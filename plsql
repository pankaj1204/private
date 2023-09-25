create Table Borrower(Roll_no integer primary key,Name Varchar(20),Issue_date Date,Book_name varchar(20),Status varchar(20));

INSERT INTO Borrower (Roll_no, Name, Issue_date, Book_name, Status)
VALUES (1, 'Prajwal', TO_DATE('2023-07-06', 'YYYY-MM-DD'), 'Book A', 'Issued');

INSERT INTO Borrower (Roll_no, Name, Issue_date, Book_name, Status)
VALUES (2, 'Pankaj', TO_DATE('2023-09-21', 'YYYY-MM-DD'), 'Book B', 'Issued');

INSERT INTO Borrower (Roll_no, Name, Issue_date, Book_name, Status)
VALUES (3, 'Sahil', TO_DATE('2023-08-25', 'YYYY-MM-DD'), 'Book C', 'Issued');

INSERT INTO Borrower (Roll_no, Name, Issue_date, Book_name, Status)
VALUES (4, 'Rohit', TO_DATE('2023-09-12', 'YYYY-MM-DD'), 'Book D', 'Issued');

INSERT INTO Borrower (Roll_no, Name, Issue_date, Book_name, Status)
VALUES (5, 'Ajit', TO_DATE('2023-09-01', 'YYYY-MM-DD'), 'Book E', 'Issued');


create table Fine(Roll_no integer,Due integer,Amt integer,foreign key(Roll_no) references Borrower(Roll_no));




