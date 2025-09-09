DROP TABLE IF EXISTS Person;
DROP TABLE IF EXISTS Student;
CREATE DATABASE ANMOL;
USE ANMOL;
CREATE TABLE Student (
    sap_id VARCHAR(15) PRIMARY KEY,
    SCHOOL_NAME VARCHAR(66) NOT NULL,
    COURSE_NAME VARCHAR(66) NOT NULL,
    name VARCHAR(66) NOT NULL
);
CREATE DATABASE THAPLIYAL;
USE THAPLIYAL;
CREATE TABLE Person (
name VARCHAR(66) NOT NULL,
adress varchar(66) NOT NULL,
phone_number VARCHAR(15) PRIMARY KEY
);
USE ANMOL;
INSERT INTO STUDENT (sap_id,SCHOOL_NAME,COURSE_NAME,name) VALUES
('590011794','School of Computer Science','B.Tech CSE','Anmol Thapliyal'),
('590014725','School of Computer Science','B.Tech CSE','Rahul Mankani'),
('590014114','School of Computer Science','B.Tech CSE','Himanshu Singh');

USE THAPLIYAL;
INSERT INTO PERSON (name,adress,phone_number) VALUES
('Anmol Thapliyal','Dehradun,Uttrakhand','9027233941'),
('Rahul Mankani','Ajmer,Rajasthan','7073646099'),
('Himanshu Singh','Kanpur,UP','6306820826');

USE ANMOL;
SELECT * FROM Student;

USE THAPLIYAL;
SELECT * FROM Person;

USE ANMOL;
SELECT 
    s.sap_id, 
    s.name, 
    s.SCHOOL_NAME, 
    s.COURSE_NAME, 
    p.adress, 
    p.phone_number
FROM ANMOL.Student s
JOIN THAPLIYAL.Person p
ON s.name=p.name;

SELECT * FROM Student WHERE SCHOOL_NAME='School of Computer Science';

SELECT COURSE_NAME,COUNT(*) AS total_students
FROM Student
GROUP BY COURSE_NAME;

UPDATE THAPLIYAL.PERSON
SET PHONE_NUMBER='9758119848'
WHERE name='Anmol Thapliyal';

USE THAPLIYAL;
SELECT * FROM PERSON;

USE ANMOL;
DELETE FROM Student 
WHERE sap_id='590014114';

SELECT * FROM STUDENT;

SELECT DATABASE();
SHOW TABLES;

DESCRIBE THAPLIYAL.Person;


