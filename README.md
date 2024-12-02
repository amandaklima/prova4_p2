Amanda Lima -00000851755
Gustavo Igor-00000851759


Para criar um modelo de Entidade-Relacionamento (ER) baseado no diagrama de classes fornecido, podemos identificar as entidades e os relacionamentos entre elas. Vou descrever as entidades, atributos e os relacionamentos principais:

### Entidades:
1. **Student**
   - **Atributos**: 
     - `id` (Long)
     - `name` (String)
     - `studentImage` (String)
     - `email` (String)
     - `password` (String)
     - `phone` (String)
     - `birth` (LocalDate)
   - **Relacionamentos**:
     - Relacionamento de **1 para muitos** com **Absence** (um aluno pode ter várias ausências).
     - Relacionamento de **1 para 1** com **Guardian** para a mãe e para o pai (um aluno tem exatamente uma mãe e um pai como responsáveis).

2. **Absence**
   - **Atributos**:
     - `id` (Long)
     - `absenceDay` (LocalDate)
     - `isJustificationValid` (boolean)
     - `justificationText` (String)
   - **Relacionamentos**:
     - Relacionamento de **muitos para 1** com **Student** (cada ausência pertence a um único aluno).

3. **Guardian**
   - **Atributos**:
     - `id` (Long)
     - `name` (String)
     - `phone` (String)
   - **Relacionamentos**:
     - Relacionamento de **1 para 1** com **Student** para mãe e pai (cada guardião está associado a um aluno).

4. **User**
   - **Atributos**:
     - `id` (Long)
     - `email` (String)
     - `password` (String)
     - `roles` (UserRoles)
   - **Relacionamentos**:
     - Relacionamento de **1 para 1** com **UserRequestDTO** (um usuário possui uma requisição de dados).
     - Relacionamento de **1 para 1** com **UserResponseDTO** (um usuário tem uma resposta de dados).

5. **UserRequestDTO**
   - **Atributos**:
     - `email` (String)
     - `password` (String)
   - **Relacionamentos**:
     - Relacionamento de **1 para 1** com **User**.

6. **UserResponseDTO**
   - **Atributos**:
     - `id` (Long)
     - `email` (String)
   - **Relacionamentos**:
     - Relacionamento de **1 para 1** com **User**.

7. **StudentResponseDTO**
   - **Atributos**:
     - `id` (Long)
     - `name` (String)
     - `studentImage` (String)
     - `birth` (LocalDate)
     - `mother` (Guardian)
     - `father` (Guardian)
     - `email` (String)
     - `password` (String)
     - `phone` (String)
     - `absences` (List<Absence>)
     - `totalAbsences` (int)
     - `totalMonthAbsences` (int)
     - `totalWeekAbsences` (int)
     - `monthFrequency` (Map<LocalDate, Boolean>)
     - `weeklyFrequency` (Map<LocalDate, Boolean>)
     - `todayDate` (LocalDate)

---

### Relacionamentos entre as entidades:

- **Student - Absence**: Um **Student** pode ter muitas **Absences**. Relacionamento de **1 para muitos**.
- **Student - Guardian**: Um **Student** tem exatamente uma **Guardian** para a mãe e para o pai, ou seja, dois relacionamentos de **1 para 1** com **Guardian**.
- **User - UserRequestDTO**: Um **User** possui exatamente um **UserRequestDTO**. Relacionamento de **1 para 1**.
- **User - UserResponseDTO**: Um **User** tem exatamente um **UserResponseDTO**. Relacionamento de **1 para 1**.

### Diagrama ER
O diagrama ER pode ser descrito visualmente, com as seguintes entidades e seus relacionamentos:

- **Student** (id, name, studentImage, email, password, phone, birth)
  - 1 -> Muitos **Absence** (id, absenceDay, isJustificationValid, justificationText)
  - 1 -> 1 **Guardian** (id, name, phone) [para mãe]
  - 1 -> 1 **Guardian** (id, name, phone) [para pai]
  
- **User** (id, email, password, roles)
  - 1 -> 1 **UserRequestDTO** (email, password)
  - 1 -> 1 **UserResponseDTO** (id, email)

---

Esse modelo ER descreve as entidades e seus relacionamentos de forma simples e clara, com base nas classes fornecidas. O próximo passo seria criar o diagrama visual com essas informações.
