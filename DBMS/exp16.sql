CLEAR SCREEN;
SET SERVEROUTPUT ON;
UNDEFINE A;

BEGIN
    EXECUTE IMMEDIATE 'DROP TABLE customers PURGE';
EXCEPTION
    WHEN OTHERS THEN NULL;
END;
/
BEGIN
    EXECUTE IMMEDIATE '
        CREATE TABLE customers (
            id NUMBER PRIMARY KEY,
            name VARCHAR2(50),
            age NUMBER,
            address VARCHAR2(100),
            salary NUMBER
        )
    ';
END;
/
INSERT INTO customers VALUES (1,'Ramesh',32,'Ahmedabad',2000);
INSERT INTO customers VALUES (2,'Khilan',25,'Delhi',1500);
INSERT INTO customers VALUES (3,'Kaushik',23,'Kota',2000);
INSERT INTO customers VALUES (4,'Chaitali',25,'Mumbai',6500);
INSERT INTO customers VALUES (5,'Hardik',27,'Bhopal',8500);
INSERT INTO customers VALUES (6,'Komal',22,'MP',4500);
COMMIT;

SELECT * FROM customers;

-- Q1
CREATE OR REPLACE TRIGGER trg_customer_salary
BEFORE INSERT OR UPDATE OR DELETE ON customers
FOR EACH ROW
DECLARE
    v_old NUMBER;
    v_new NUMBER;
BEGIN
    IF UPDATING OR DELETING THEN
        v_old:=:OLD.salary;
    END IF;
    IF INSERTING OR UPDATING THEN
        v_new:=:NEW.salary;
    END IF;
    IF INSERTING THEN
        DBMS_OUTPUT.PUT_LINE('INSERT OPERATION: New Salary ='||v_new);
    ELSIF UPDATING THEN
        DBMS_OUTPUT.PUT_LINE('UPDATE OPERATION: Old Salary ='||v_old ||
                            '| New Salary =' || v_new ||
                            '| Difference =' || (v_new-v_old));
    ELSIF DELETING THEN
        DBMS_OUTPUT.PUT_LINE('DELETE OPERATION: Deleted Salary ='||v_old);
    END IF;
END;
/
INSERT INTO customers VALUES (7,'Demo',30,'TestCity',3000);
UPDATE customers SET salary=9000 WHERE id=4;
DELETE FROM customers WHERE id=3;
COMMIT;
/
SELECT * FROM customers;

