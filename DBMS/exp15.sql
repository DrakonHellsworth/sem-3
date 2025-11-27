CLEAR SCREEN;
SET SERVEROUTPUT ON;
UNDEFINE A;

BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE employees PURGE';
EXCEPTION
    WHEN OTHERS THEN NULL;
END;
/
BEGIN
    EXECUTE IMMEDIATE '
        CREATE TABLE employees (
            employee_id NUMBER PRIMARY KEY,
            first_name  VARCHAR2(50),
            last_name   VARCHAR2(50),
            salary      NUMBER
        )
    ';
END;
/
INSERT INTO employees VALUES (101,'John','Doe',2000);
INSERT INTO employees VALUES (102,'Alice','Smith',3000);
INSERT INTO employees VALUES (103,'Bob','Brown',5000);
INSERT INTO employees VALUES (104,'Lara','King',8000);
INSERT INTO employees VALUES (105,'Sam','Bose',1000);
COMMIT;

-- Q1: IMPLICIT CURSOR – Increase salary by 10%
CREATE OR REPLACE PROCEDURE update_salary AS
    v_count NUMBER;
BEGIN
    UPDATE employees
    SET salary = salary * 1.10;
    v_count := SQL%ROWCOUNT;
    IF v_count>0 THEN
        DBMS_OUTPUT.PUT_LINE(v_count || 'records updated.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('No Change');
    END IF;
END;
/
BEGIN
    update_salary;
END;
/

-- Q2: EXPLICIT CURSOR-Display employee_id,name,salary
CREATE OR REPLACE PROCEDURE show_employees AS
    CURSOR emp_cur IS
        SELECT employee_id, first_name, salary
        FROM employees;
    v_id   employees.employee_id%TYPE;
    v_name employees.first_name%TYPE;
    v_sal  employees.salary%TYPE;
BEGIN
    OPEN emp_cur;
    LOOP
        FETCH emp_cur INTO v_id, v_name, v_sal;
        EXIT WHEN emp_cur%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(
            'ID: ' || v_id ||
            '  Name: ' || v_name ||
            '  Salary: ' || v_sal
        );
    END LOOP;
    CLOSE emp_cur;
END;
/
BEGIN
    show_employees;
END;
/

-- Q3: EXPLICIT CURSOR – Insert into TEMP_EMP
BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE temp_emp PURGE';
EXCEPTION
    WHEN OTHERS THEN NULL;
END;
/
BEGIN
    EXECUTE IMMEDIATE '
        CREATE TABLE temp_emp (
            employee_id NUMBER,
            last_name   VARCHAR2(50),
            salary      NUMBER
        )
    ';
END;
/
CREATE OR REPLACE PROCEDURE fill_temp_emp AS
    CURSOR high_sal IS
        SELECT employee_id, last_name, salary
        FROM employees
        WHERE salary>2500;
    v_id    employees.employee_id%TYPE;
    v_lname employees.last_name%TYPE;
    v_sal   employees.salary%TYPE;
BEGIN
    OPEN high_sal;
    LOOP
        FETCH high_sal INTO v_id, v_lname, v_sal;
        EXIT WHEN high_sal%NOTFOUND;
        INSERT INTO temp_emp (employee_id, last_name, salary)
        VALUES (v_id, v_lname, v_sal);
    END LOOP;
    CLOSE high_sal;
    DBMS_OUTPUT.PUT_LINE('Records inserted into TEMP_EMP.');
END;
/
BEGIN
    fill_temp_emp;
END;
/
SELECT * FROM temp_emp;
/
