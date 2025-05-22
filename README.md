# Sistema de Gerenciamento Acadêmico em C (Em desenvolvimento)

Este projeto é um sistema acadêmico simples, desenvolvido em linguagem C, com o objetivo de praticar conceitos de estrutura de dados, alocação dinâmica de memória e manipulação de structs. Ele permite o cadastro e gerenciamento de alunos, disciplinas, matrículas e compromissos acadêmicos.
  
Algumas funcionalidades ainda não foram implementadas ou finalizadas. Este projeto está sendo desenvolvido como prática de programação em C.

---

## Funcionalidades (parcialmente implementadas)

- [x] Cadastro de alunos (com verificação de e-mail)
- [x] Cadastro de disciplinas
- [x] Cadastro de matrículas (relacionando alunos e disciplinas)
- [x] Cadastro de compromissos com data e hora
- [x] Relatórios de compromissos:
  - De um aluno específico (ordenado por data/hora)
  - De todos os alunos (ordenado por RA, data e hora)
  - Por data específica
  - De todas as datas
- [x] Relatórios de dados dos alunos
- [ ] Salvamento e carregamento de dados via arquivos (a implementar)
- [ ] Validação e melhoria das entradas de dados
- [ ] Interface textual mais amigável

---

## Estrutura de Dados

O sistema é baseado nas seguintes estruturas:

- `td_aluno`: Armazena dados de alunos (RA, nome, e-mail)
- `td_disciplina`: Guarda informações sobre disciplinas
- `td_matricula`: Relaciona alunos com disciplinas e notas
- `td_compromisso`: Representa compromissos de alunos com data, hora e descrição
- `td_data` e `td_hora`: Utilizadas para organizar e validar datas e horários

---


