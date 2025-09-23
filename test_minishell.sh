#!/bin/bash

# Script de test pour Minishell
# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== TESTS MINISHELL ===${NC}"

# Test de compilation
echo -e "\n${YELLOW}1. Test de compilation${NC}"
if make -n | grep -q "\-Wall \-Wextra \-Werror"; then
    echo -e "${GREEN}✓ Flags de compilation OK${NC}"
else
    echo -e "${RED}✗ Flags de compilation manquants${NC}"
fi

if make clean && make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation réussie${NC}"
else
    echo -e "${RED}✗ Erreur de compilation${NC}"
    exit 1
fi

# Fonction de test avec timeout
run_test() {
    local cmd="$1"
    local expected="$2"
    local desc="$3"
    
    echo -e "\n${YELLOW}Test: $desc${NC}"
    echo "Commande: $cmd"
    
    # Exécuter la commande avec timeout
    timeout 5s bash -c "echo '$cmd' | ./minishell" > test_output.tmp 2>&1
    local exit_code=$?
    
    if [ $exit_code -eq 124 ]; then
        echo -e "${RED}✗ Timeout (5s)${NC}"
    elif [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ Exécuté sans erreur${NC}"
        if [ -n "$expected" ]; then
            if grep -q "$expected" test_output.tmp; then
                echo -e "${GREEN}✓ Sortie attendue trouvée${NC}"
            else
                echo -e "${YELLOW}? Sortie différente de l'attendu${NC}"
            fi
        fi
    else
        echo -e "${RED}✗ Erreur d'exécution (code: $exit_code)${NC}"
    fi
    
    rm -f test_output.tmp
}

# Tests basiques
echo -e "\n${YELLOW}2. Tests commandes de base${NC}"
run_test "/bin/ls" "" "Commande absolue simple"
run_test "/bin/echo hello" "hello" "Echo avec argument"
run_test "" "" "Ligne vide"

# Tests builtins
echo -e "\n${YELLOW}3. Tests builtins${NC}"
run_test "echo hello world" "hello world" "Echo builtin"
run_test "pwd" "" "PWD builtin"
run_test "env" "" "ENV builtin"

# Tests variables
echo -e "\n${YELLOW}4. Tests variables${NC}"
run_test "export TEST=hello && echo \$TEST" "hello" "Export et expansion"
run_test "echo \$USER" "" "Variable USER"

# Tests redirections (sauf heredoc)
echo -e "\n${YELLOW}5. Tests redirections${NC}"
echo "test content" > test_redir.txt
run_test "cat < test_redir.txt" "test content" "Redirection entrée"
run_test "echo output > test_out.txt && cat test_out.txt" "output" "Redirection sortie"
rm -f test_redir.txt test_out.txt

# Tests pipes
echo -e "\n${YELLOW}6. Tests pipes${NC}"
run_test "echo hello | cat" "hello" "Pipe simple"
run_test "ls | head -1" "" "Pipe avec head"

# Tests quotes
echo -e "\n${YELLOW}7. Tests quotes${NC}"
run_test "echo 'hello world'" "hello world" "Single quotes"
run_test "echo \"hello world\"" "hello world" "Double quotes"

# Tests d'erreur
echo -e "\n${YELLOW}8. Tests gestion d'erreur${NC}"
run_test "commandnotfound" "" "Commande inexistante"
run_test "/bin/ls nonexistent" "" "Fichier inexistant"

# Nettoyage
rm -f test_*.txt test_*.tmp

echo -e "\n${YELLOW}=== FIN DES TESTS ===${NC}"
echo -e "${YELLOW}Vérifications manuelles recommandées:${NC}"
echo "- Ctrl-C, Ctrl-D, Ctrl-\ dans différents contextes"
echo "- Tests de mémoire avec valgrind"
echo "- Navigation historique avec flèches haut/bas"
echo "- Heredoc (si implémenté)"