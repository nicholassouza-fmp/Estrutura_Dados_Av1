nomes = []
notas = []

MEDIA_APROVACAO = 7.0


def ler_opcao(mensagem, minimo, maximo):
  
    while True:
        entrada = input(mensagem).strip()
        try:
            opcao = int(entrada)
        except ValueError:
            print("Valor inválido. Digite um número inteiro.")
            continue

        if minimo <= opcao <= maximo:
            return opcao

        print(f"Opção inválida. Digite um valor entre {minimo} e {maximo}.")

def ler_inteiro(mensagem):
    
    while True:
        entrada = input(mensagem).strip()
        try:
            return int(entrada)
        except ValueError:
            print("Valor inválido. Digite um número inteiro.")

def exibir_menu():
    print("\n ========== SISTEMA DE GESTÃO DE NOTAS ==========")
    print("1 - Cadastro de alunos e notas")
    print("2 - Lista de alunos e notas")
    print("3 - Calcular a média geral da turma")
    print("4 - Maior e menor nota registrada")
    print("5 - Alunos aprovados")
    print("6 - Estatísticas recursivas")
    print("7 - Funcionalidades extras")
    print("0 - Encerrar sistema")

def cadastrar_aluno(nomes_lst, notas_lst):
    print("\n === Cadastro de Alunos e Notas ===")
    while True:
        nome = input("Nome do aluno: ").strip()

        if nome and all(caractere.isalpha() or caractere.isspace() for caractere in nome):
            break

        print("Nome inválido. Digite somente letras e espaços.")

    nota_valida = False
    nota = 0.0

    while not nota_valida:
        entrada = input("Nota (0.0 a 10.0): ").strip().replace(",", ".")
        try:
            nota = float(entrada)
        except ValueError:
            print("Valor invalido. Digite um numero.")
            continue

        if not validar_nota(nota):
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

def validar_nota(nota):
    return 0.0 <= nota <= 10.0

def buscar_aluno_sequencial(nomes, nome_busca):
    for i in range(len(nomes)):
        if nomes[i] == nome_busca:
            return i
    return -1

def buscar_aluno_por_nome(nomes, notas):
    if not nomes:
        print("\nNenhum aluno cadastrado.")
        return

    nome_busca = input("\nDigite o nome do aluno a buscar: ").strip()
    pos = buscar_aluno_sequencial(nomes, nome_busca)
    if pos >= 0:
        print(f"Aluno encontrado na posicao {pos + 1} - Nota: {notas[pos]:.2f}")
    else:
        print("Aluno nao encontrado.")

def calcular_percentual_aprovacao(aprovados, total):
    if total == 0:
        return 0.0
    return (aprovados / total) * 100

def contar_acima_da_media(notas, media):
    count = 0
    for nota in notas:
        if nota > media:
            count += 1
    return count

def exibir_estatisticas_complementares(notas):
    if not notas:
        print("\nNenhum aluno cadastrado.")
        return

    total = len(notas)
    soma = 0.0
    for nota in notas:
        soma += nota
    media = soma / total

    aprovados = contar_aprovados_recursivo(notas, total)
    percentual = calcular_percentual_aprovacao(aprovados, total)
    acima_da_media = contar_acima_da_media(notas, media)

    print("\n=== ESTATÍSTICAS COMPLEMENTARES ===")
    print(f"Percentual de aprovacao : {percentual:.2f}%")
    print(f"Alunos acima da media da turma ({media:.2f}): {acima_da_media}")

def soma_digitos_recursivo(n):
    n = abs(n)
    if n == 0:
        return 0
    return (n % 10) + soma_digitos_recursivo(n // 10)

def calcular_soma_digitos():
    numero = ler_inteiro("\nDigite um numero inteiro: ")
    print(f"Soma dos digitos: {soma_digitos_recursivo(numero)}")

def exibir_invertido_recursivo(nomes, notas, indice):
    if indice < 0:
        return
    print(f"- Aluno: {nomes[indice]:<20} | Nota: {notas[indice]:.1f}")
    exibir_invertido_recursivo(nomes, notas, indice - 1)

def exibir_listagem_invertida(nomes, notas):
    if not nomes:
        print("\nNenhum aluno cadastrado.")
        return
    print("\n=== LISTAGEM INVERTIDA (RECURSIVA) ===")
    exibir_invertido_recursivo(nomes, notas, len(nomes) - 1)

def submenu_extras(nomes, notas):
    while True:
        print("\n----- Submenu de Extras -----")
        print("1 - Buscar aluno por nome (busca sequencial)")
        print("2 - Estatisticas complementares (% aprovacao / acima da media)")
        print("3 - Soma dos digitos de um numero (recursivo)")
        print("4 - Exibir listagem invertida (recursivo)")
        print("0 - Voltar ao menu principal")

        opcao_extra = ler_opcao("Escolha uma opção: ", 0, 4)

        match opcao_extra:
            case 1:
                buscar_aluno_por_nome(nomes, notas)
            case 2:
                exibir_estatisticas_complementares(notas)
            case 3:
                calcular_soma_digitos()
            case 4:
                exibir_listagem_invertida(nomes, notas)
            case 0:
                print("Voltando ao menu principal...")
                return

def menu():
    while True:
        exibir_menu()
        opcao = ler_opcao("Escolha uma opção: ", 0, 7)

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
            case 7:
                submenu_extras(nomes, notas)
            case 0:
                print("\nSistema Encerrado!")
                return


if __name__ == "__main__":
    menu()
