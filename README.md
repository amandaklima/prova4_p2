erDiagram
    STUDENT {
        Long id
        String name
        String studentImage
        String email
        String password
        String phone
        LocalDate birth
    }
    
    ABSENCE {
        Long id
        LocalDate absenceDay
        boolean isJustificationValid
        String justificationText
    }

    GUARDIAN {
        Long id
        String name
        String phone
    }

    USER {
        Long id
        String email
        String password
        UserRoles roles
    }

    USER_REQUEST_DTO {
        String email
        String password
    }

    USER_RESPONSE_DTO {
        Long id
        String email
    }

    STUDENT_RESPONSE_DTO {
        Long id
        String name
        String studentImage
        LocalDate birth
        Guardian mother
        Guardian father
        String email
        String password
        String phone
        List<Absence> absences
        int totalAbsences
        int totalMonthAbsences
        int totalWeekAbsences
        Map<LocalDate, Boolean> monthFrequency
        Map<LocalDate, Boolean> weeklyFrequency
        LocalDate todayDate
    }

    STUDENT ||--o| ABSENCE : has
    STUDENT ||--|| GUARDIAN : hasMother
    STUDENT ||--|| GUARDIAN : hasFather
    USER ||--|| USER_REQUEST_DTO : hasRequestDTO
    USER ||--|| USER_RESPONSE_DTO : hasResponseDTO
