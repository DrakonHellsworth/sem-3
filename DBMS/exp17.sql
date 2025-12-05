CLEAR SCREEN;
SET SERVEROUTPUT ON;
UNDEFINE A;

BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE employee PURGE';
EXCEPTION
    WHEN OTHERS THEN NULL;
END;
/
BEGIN
    EXECUTE IMMEDIATE '
        CREATE TABLE employee (
            fname VARCHAR2(15),
            minit CHAR(1),
            lname VARCHAR2(15),
            ssn CHAR(9) PRIMARY KEY,
            bdate DATE,
            address VARCHAR2(30),
            sex CHAR(1),
            salary NUMBER,
            supervisor_ssn CHAR(9),
            dno NUMBER
        )
    ';
END;
/

INSERT ALL
INTO employee VALUES ('John','B','Smith','123456789',DATE '1965-01-09','731 Fondren, Houston TX','M',30000,'333445555',5)
INTO employee VALUES ('Franklin','T','Wong','333445555',DATE '1965-12-08','638 Voss, Houston TX','M',40000,'888665555',5)
INTO employee VALUES ('Alicia','J','Zelaya','999887777',DATE '1968-01-19','3321 Castle, Spring TX','F',25000,'987654321',4)
INTO employee VALUES ('Jennifer','S','Wallace','987654321',DATE '1941-06-20','291 Berry, Bellaire TX','F',43000,'888665555',4)
INTO employee VALUES ('Ramesh','K','Narayan','666884444',DATE '1962-09-15','975 Fire Oak, Humble TX','M',38000,'333445555',5)
INTO employee VALUES ('Joyce','A','English','453453453',DATE '1972-07-31','5631 Rice, Houston TX','F',25000,'333445555',5)
INTO employee VALUES ('Ahmad','V','Jabbar','987987987',DATE '1969-03-29','980 Dallas, Houston TX','M',25000,'987654321',4)
INTO employee VALUES ('James','E','Borg','888665555',DATE '1937-11-10','450 Stone, Houston TX','M',55000,NULL,1)
SELECT * FROM dual;
COMMIT;

CREATE OR REPLACE TRIGGER salary_violation
BEFORE INSERT OR UPDATE OF salary, supervisor_ssn
ON employee
FOR EACH ROW
DECLARE
    v_old_sal employee.salary%TYPE;
    v_new_sal employee.salary%TYPE;
    v_old_super employee.supervisor_ssn%TYPE;
    v_new_super employee.supervisor_ssn%TYPE;
BEGIN
    IF INSERTING THEN
        v_new_sal := :NEW.salary;
        v_new_super := :NEW.supervisor_ssn;
        DBMS_OUTPUT.PUT_LINE(
            'INSERT → Salary = ' || v_new_sal ||
            ' | Supervisor SSN = ' || v_new_super
        );
    ELSIF UPDATING THEN
        v_old_sal := :OLD.salary;
        v_new_sal := :NEW.salary;
        v_old_super := :OLD.supervisor_ssn;
        v_new_super := :NEW.supervisor_ssn;
        DBMS_OUTPUT.PUT_LINE(
            'UPDATE → Old Salary = ' || v_old_sal ||
            ' | New Salary = ' || v_new_sal ||
            ' | Old Supervisor = ' || v_old_super ||
            ' | New Supervisor = ' || v_new_super ||
            ' | Salary Difference = ' || (v_new_sal - v_old_sal)
        );
    END IF;
END;
/

INSERT INTO employee VALUES
('Test','X','User','111111111',DATE '1990-01-01','Test Addr','M',32000,'987654321',5);

UPDATE employee SET salary = 60000 WHERE ssn = '333445555';

UPDATE employee SET supervisor_ssn = '123456789' WHERE ssn = '999887777';

COMMIT;

SELECT * FROM employee;
/
