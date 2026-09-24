nomes = []
notas = []

MEDIA_APROVACAO = 7.0


def exibir_menu():
    print("\n ========== SISTEMA DE GESTÃO DE NOTAS ==========")
    print("1 - Cadastro de alunos e notas")
    print("2 - Lista de alunos e notas")
    print("3 - Calcular a média geral da turma")
    print("4 - Maior e menor nota registrada")
    print("5 - Alunos aprovados")
    print("6 - Estatísticas recursivas")
    print("0 - Encerrar sistema")


def cadastrar_aluno(nomes_lst, notas_lst):
    print("\n === Cadastro de Alunos e Notas ===")
    nome = input("Nome do aluno: ").strip()

    nota_valida = False
    nota = 0.0

    while not nota_valida:
        entrada = input("Nota (0.0 a 10.0): ").strip().replace(",", ".")
        try:
            nota = float(entrada)
        except ValueError:
            print("Valor invalido. Digite um numero.")
            continue

        if nota < 0.0 or nota > 10.0:
            print("Nota fora do intervalo permitido.")
        else:
            nota_valida = True

    nomes_lst.append(nome)
    notas_lst.append(nota)

    print(f"Aluno cadastrado com sucesso! ({len(nomes_lst)} cadastrados)\n")

def calcular_media_turma(notas):
    qtd_alunos = len(notas)
    if qtd_alunos == 0:
        return 0.0
        
    soma = 0.0
    for nota in notas:
        soma += nota
    media = soma/qtd_alunos
        
    print(f"\nMÉDIA DA TURMA: {media:.2f} ")

def exibir_extremos_notas(nomes, notas):
    qtd_alunos = len(notas)
    if qtd_alunos == 0:
        return
        
    indice_maior = 0
    indice_menor = 0
    
    for i in range(1, qtd_alunos):
        if notas[i] > notas[indice_maior]:
            indice_maior = i
        if notas[i] < notas[indice_menor]:
            indice_menor = i
            
    print(f"Maior nota: {notas[indice_maior]:.2f} (Aluno: {nomes[indice_maior]})")
    print(f"Menor nota: {notas[indice_menor]:.2f} (Aluno: {nomes[indice_menor]})")

def exibir_alunos(nomes, notas):
    if not nomes:
        print("\nNenhum aluno cadastrado.")
        return

    print("\n=== LISTAGEM GERAL DE ALUNOS ===")
    for i in range(len(nomes)):
        print(f"{i + 1}. Aluno: {nomes[i]:<20} | Nota: {notas[i]:.1f}")

def listar_aprovados(nomes, notas):
    if not nomes:
        print("\nNenhum aluno cadastrado.")
        return

    aprovados = 0
    print("\n=== ALUNOS APROVADOS (Nota >= 7.0) ===")
    for i in range(len(nomes)):
        if notas[i] >= 7.0:
            print(f"- Aluno: {nomes[i]:<20} | Nota: {notas[i]:.1f}")
            aprovados += 1

    print("-" * 40)
    print(f"Total de discentes aprovados: {aprovados}")

def soma_recursiva(notas, total):
    if total == 0:
        return 0
    return notas[total - 1] + soma_recursiva(notas, total - 1)

def contar_aprovados_recursivo(notas, total):
    if total == 0:
        return 0
    if notas[total - 1] >= MEDIA_APROVACAO:
        aprovado_atual = 1
    else:
        aprovado_atual = 0
    return aprovado_atual + contar_aprovados_recursivo(notas, total - 1)

def exibir_estatisticas_recursivas(notas):
    if not notas:
        print("\nNenhum aluno cadastrado.")
        return

    total = len(notas)
    soma = soma_recursiva(notas, total)
    media = soma / total
    aprovados = contar_aprovados_recursivo(notas, total)

    print("\n=== ESTATÍSTICAS RECURSIVAS ===")
    print(f"Soma total das notas : {soma:.1f}")
    print(f"Média da turma        : {media:.2f}")
    print(f"Total de aprovados    : {aprovados}")


def menu():
    opcao = None

    while opcao != 0:
        exibir_menu()
        opcao = int(input("Escolha uma opção: "))

        match opcao:
            case 1:
                cadastrar_aluno(nomes, notas)
            case 2:
                exibir_alunos(nomes, notas)
            case 3:
                calcular_media_turma(notas)
            case 4:
                exibir_extremos_notas(nomes, notas)
            case 5:
                listar_aprovados(nomes, notas)
            case 6:
                exibir_estatisticas_recursivas(notas)
            case 0:
                print("\nSistema Encerrado!")


if __name__ == "__main__":
    menu()