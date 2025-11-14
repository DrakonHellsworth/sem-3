CLEAR SCREEN;
SET SERVEROUTPUT ON;
UNDEFINE A B C N1 N2 N3;

-- Q1
DECLARE
    A NUMBER := &A;
    B NUMBER := &B;
    C NUMBER := &C;
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
-- Q2
DECLARE
    i NUMBER := 1;
BEGIN
    WHILE i <= 20 LOOP
        DBMS_OUTPUT.PUT_LINE('Welcome to PL/SQL Programming');
        i := i + 1;
    END LOOP;
END;
/
-- Q3
DECLARE
    n NUMBER := &N1;
    fact NUMBER := 1;
    i NUMBER;
BEGIN
    FOR i IN 1..n LOOP
        fact := fact * i;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Factorial of ' || n || ' = ' || fact);
END;
/
-- Q4
DECLARE
    n NUMBER := &N2;
    a NUMBER := 0;
    b NUMBER := 1;
    c NUMBER;
    i NUMBER;
BEGIN
    DBMS_OUTPUT.PUT_LINE(a);
    DBMS_OUTPUT.PUT_LINE(b);

    FOR i IN 3..n LOOP
        c := a + b;
        DBMS_OUTPUT.PUT_LINE(c);
        a := b;
        b := c;
    END LOOP;
END;
/
-- Q5
DECLARE
    n NUMBER := &N3;
    s NUMBER := 0;
    i NUMBER;
BEGIN
    FOR i IN 1..n LOOP
        s := s + i;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Sum of first ' || n || ' numbers = ' || s);
END;
/
