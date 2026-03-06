import pexpect
import subprocess
import sys
import time
import re

MINISHELL = "./bin/minishell"

class C:
    RESET = '\033[0m'
    GREEN = '\033[1;32m'
    RED = '\033[1;31m'
    BLUE = '\033[1;34m'
    CYAN = '\033[1;36m'
    YELLOW = '\033[1;33m'

print(f"{C.BLUE}================ MINISHELL PYTHON TESTER ================{C.RESET}\n")

def clean_output(text, cmd):
    # 1. Supprimer les couleurs ANSI
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])|[\x01\x02]')
    clean_text = ansi_escape.sub('', text)
    
    # 2. Supprimer ton prompt
    prompt_str = "cyril@losmachinos🏭 ~/minishell"
    clean_text = clean_text.replace(prompt_str, "")
    
    # 3. NOUVEAU : Supprimer la commande répétée par readline
    clean_text = clean_text.strip()
    if clean_text.startswith(cmd):
        clean_text = clean_text[len(cmd):].strip()
        
    # 4. Supprimer le "exit" automatique de fin (EOF)
    if clean_text.endswith("exit"):
        clean_text = clean_text[:-4].strip()
        
    return clean_text

def run_standard_test(category, cmd):
    # INJECTION DIRECTE VIA STDIN
    bash_proc = subprocess.run(["bash", "--posix"], input=cmd + "\n", text=True, capture_output=True)
    bash_out = bash_proc.stdout.strip()
    bash_exit = bash_proc.returncode

    mini_proc = subprocess.run([MINISHELL], input=cmd + "\n", text=True, capture_output=True)
    mini_out = clean_output(mini_proc.stdout, cmd)
    mini_exit = mini_proc.returncode

    if bash_out == mini_out and bash_exit == mini_exit:
        print(f"{C.CYAN}{category:<15}{C.RESET} | {cmd:<35} | {C.GREEN}[OK]{C.RESET}")
    else:
        print(f"{C.CYAN}{category:<15}{C.RESET} | {cmd:<35} | {C.RED}[KO]{C.RESET}")
        print(f"   {C.YELLOW}Bash (Exit {bash_exit}){C.RESET}: {bash_out[:200]}")
        print(f"   {C.RED}Mini (Exit {mini_exit}){C.RESET}: {mini_out[:200]}")

print(f"{C.BLUE}--- TESTS DE BASE ---{C.RESET}")
run_standard_test("Basique", "ls -la")
run_standard_test("Quotes", "echo 'hello $USER'")
run_standard_test("Expand", "export A=\"cat main.c\" ; echo $A")
run_standard_test("Pipes", "ls | grep a | wc -l")
run_standard_test("Redir", "echo test > out.txt ; cat out.txt ; rm out.txt")
run_standard_test("Erreur", "commande_inexistante")

print(f"\n{C.BLUE}--- TESTS INTERACTIFS (SIGNAUX & EOF) ---{C.RESET}")
def test_ctrl_c_empty():
    print(f"{C.CYAN}Signal_INT_Vide{C.RESET} | Test Ctrl+C sur un prompt vide... ", end="", flush=True)
    try:
        child = pexpect.spawn(MINISHELL, encoding='utf-8', timeout=2)
        child.expect('.*') 
        child.sendline('\x03')
        child.expect('.*')
        print(f"{C.GREEN}[OK]{C.RESET}")
        child.terminate(force=True)
    except Exception:
        print(f"{C.RED}[KO]{C.RESET} (Crash ou pas de nouveau prompt)")

def test_ctrl_d():
    print(f"{C.CYAN}Signal_EOF{C.RESET}      | Test Ctrl+D (EOF) sur prompt vide... ", end="", flush=True)
    try:
        child = pexpect.spawn(MINISHELL, encoding='utf-8', timeout=2)
        child.expect('.*')
        child.send('\x04')
        child.expect(pexpect.EOF)
        print(f"{C.GREEN}[OK]{C.RESET}")
    except Exception:
        print(f"{C.RED}[KO]{C.RESET} (Le shell ne s'est pas fermé proprement)")

def test_ctrl_backslash():
    print(f"{C.CYAN}Signal_QUIT{C.RESET}     | Test Ctrl+\\ sur prompt vide... ", end="", flush=True)
    try:
        child = pexpect.spawn(MINISHELL, encoding='utf-8', timeout=2)
        child.expect('.*')
        child.send('\x1c')
        time.sleep(0.5)
        if child.isalive():
            print(f"{C.GREEN}[OK]{C.RESET}")
        else:
            print(f"{C.RED}[KO]{C.RESET} (Le shell a crashé)")
        child.terminate(force=True)
    except Exception:
        print(f"{C.RED}[KO]{C.RESET}")

test_ctrl_c_empty()
test_ctrl_d()
test_ctrl_backslash()

print(f"\n{C.BLUE}--- TESTS VALGRIND (LEAKS) ---{C.RESET}")
def run_valgrind_test(cmd):
    print(f"{C.CYAN}Leak Check{C.RESET}      | {cmd:<35} | ", end="", flush=True)
    val_args = ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--suppressions=readline.supp", "--errors-exitcode=42", MINISHELL]
    proc = subprocess.run(val_args, input=cmd + "\n", text=True, capture_output=True)
    if proc.returncode == 42:
        print(f"{C.RED}[LEAKS DETECTED]{C.RESET}")
    else:
        print(f"{C.GREEN}[CLEAN]{C.RESET}")

run_valgrind_test("ls -l | wc -l")
run_valgrind_test("export A=B ; echo $A")
run_valgrind_test("cat << EOF\ntest\nEOF")

print(f"\n{C.BLUE}================ FIN DES TESTS ================={C.RESET}")
