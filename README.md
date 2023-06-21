# Programa de Conversões (P/Morse <-> p/Alfa)

## Especificação do programa
- Link :[Especificação](documentacao/TP3.pdf)

##  Compilando o programa

Para compilar codigo
```bash
make 
``` 
Limpar arquivos binários
```bash
make clean
```

Programa utiliza árvore binária para conversão de morse para alfanúmerico ou vice-versa, recomenda-se executar primeiro o programa da seguinte forma:

```bash
./main -i
```
Para exibir a árvore e os caracteres asc2 disponíveis.
Ou utilizando a tabela:

![TabelaMorse](documentacao/tabela-morse.png)

## Rodando o programa

O diretório **input/** é destinado a colocar os arquivos **.txt** de entrada, cada resposta do servidor de morse para alfanúmerico ou o contrário além de ser exibido no console também é criado uma arquivo de saída com o resultado da conversão para o diretório **/out** 

O programa para rodar utiliza argumentos, abaixo serão listados os argumentos disponíveis e exemplos:
- **-i** exibi os caracteres disponíveis na arvore morse e seus respectivos códigos morse:
Exemplo :
```bash
./main -i
```
- **-a** converte um arquivo com texto em alfanúmericos para morse
Exemplo :
```bash
./main input/<arquivo_alfa.txt> -a
```
- **-m** converte um arquivo com texto em morse para alfanúmerico.
Exemplo :
```bash
./main input/<arquivo_morse.txt> -m
```
- **Desenvolvido por** : [Geraldo Arthur Detomi](https://github.com/ArthurDetomi) 

<img src="https://avatars.githubusercontent.com/u/99772832?v=4" style="width:100px;margin-left:50px;border-radius:50px;">


- **Documentação :** Rhayan e Rodrigo

<img src="https://avatars.githubusercontent.com/u/102100725?v=4" style="width:100px;margin-left:50px;border-radius:50px;">