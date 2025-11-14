CLEAR SCREEN;
SET SERVEROUTPUT ON;
UNDEFINE A B C N1 N2 N3;

-- Q1
CREATE OR REPLACE PROCEDURE greatest_num(A NUMBER, B NUMBER, C NUMBER) AS
BEGIN
    IF A > B AND A > C THEN
        DBMS_OUTPUT.PUT_LINE('A is greatest: ' || A);
    ELSIF B > A AND B > C THEN
        DBMS_OUTPUT.PUT_LINE('B is greatest: ' || B);
    ELSE
        DBMS_OUTPUT.PUT_LINE('C is greatest: ' || C);
    END IF;
END;
/
BEGIN
    greatest_num(&A, &B, &C);
END;
/
-- Q2
CREATE OR REPLACE PROCEDURE print_message IS
    i NUMBER := 1;
BEGIN
    WHILE i <= 20 LOOP
        DBMS_OUTPUT.PUT_LINE('Welcome to PL/SQL Programming');
        i := i + 1;
    END LOOP;
END;
/
BEGIN
    print_message;
END;
/
-- Q3
CREATE OR REPLACE FUNCTION factorial(n NUMBER) RETURN NUMBER AS
    f NUMBER := 1;
BEGIN
    FOR i IN 1..n LOOP
        f := f * i;
    END LOOP;
    RETURN f;
END;
/
CREATE OR REPLACE PROCEDURE show_factorial(n NUMBER) AS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Factorial of ' || n || ' = ' || factorial(n));
END;
/
BEGIN
    show_factorial(&N1);
END;
/
-- Q4
CREATE OR REPLACE PROCEDURE fibonacci(n NUMBER) AS
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
BEGIN
    IF n >= 1 THEN DBMS_OUTPUT.PUT_LINE(a); END IF;
    IF n >= 2 THEN DBMS_OUTPUT.PUT_LINE(b); END IF;
    FOR i IN 3..n LOOP
        c := a + b;
        DBMS_OUTPUT.PUT_LINE(c);
        a := b;
        b := c;
    END LOOP;
END;
/
BEGIN
    fibonacci(&N2);
END;
/
-- Q5
CREATE OR REPLACE FUNCTION sum_n(n NUMBER) RETURN NUMBER AS
    s NUMBER := 0;
BEGIN
    FOR i IN 1..n LOOP
        s := s + i;
    END LOOP;
    RETURN s;
END;
/
CREATE OR REPLACE PROCEDURE show_sum(n NUMBER) AS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Sum of first ' || n || ' numbers = ' || sum_n(n));
END;
/
BEGIN
    show_sum(&N3);
END;
/
