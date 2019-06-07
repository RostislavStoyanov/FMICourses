set schema 'fn45244';

/* Populate Departments*/
INSERT INTO Department(DepNo,Name,Address)
VALUES 	(1,'A','Address A'),
	(2,'B','Address B'),
	(3,'C','Address C');

/* Populate Publisher */
INSERT INTO Publisher(Name,Address)
VALUES ('Pearson','Pearson Address');

/* Populate Person 
	Random generated strings of length 10 and names */

INSERT INTO Person (PersonalNo, Name)
VALUES	('7327774267','Kiril Aleksandrov'),
	('9514780291','Ivana Kaloyanova'),
	('7552519423','Thomas Connolly'),
	('5868822579','Carolyn Begg'),
	('4529605119','Hector Garcia-Molina'),
	('3192495355','Jeffrey D. Ullman'),
	('6447180207','Jennifer Widom ');

INSERT INTO Person (PersonalNo, Name, Salary, SuperiorPersonalNo, Position, DepNo) 
VALUES 	('8617995849', 'Daniel Savov', 2000, NULL, 'Head of Library and dep 1', 1),
	('5882713514', 'Ognian Ivanov', '1500', '8617995849', 'Head of Dep 2', '2'),
	('1109589369', 'Hristo Kirilov', 1500, '8617995849', 'Head of Dep 3', 3),
	('2216765139', 'Ludmil Petrov', 1200, '5882713514', 'Librarian', 2),
	('4175332818', 'Ralitsa Lyudmilova', 1200, '8617995849', 'Librarian',1),
	('0635190360', 'Mihaela Aleksandrova', 1200, '8617995849', 'Librarian',1),
	('8713377078', 'Svetlana Andreyeva', 1200, '5882713514', 'Librarian',2),
	('1352324154', 'Iliana Andonova', 1200, '1109589369', 'Librarian',3);
	

/* Populate Reader */
INSERT INTO Reader(ReaderID,RegistrationDate,ExpirationDate)
VALUES 	(1,'2018-06-18','2019-06-18'),
	(2,'2019-02-11','2020-02-11');

/* Populate Registered */
INSERT INTO Registered(PersonalNo,ReaderID)
VALUES 	('7327774267',1),
	('9514780291',2);
		
/* Populate Fines */

/* Populate Book */  
INSERT INTO Book(ISBN,Title,Pages,Edition,BackType,PublisherID,PublishDate)
VALUES	('9780131873254','Database Systems: The Complete Book',1248,2,'Paperback',1,'2008-06-15'),
	('9780132943260','Database Systems: A Practical Approach to Design, Implementation, and Management',1440,6,'Paperback',1,'2014-01-18');

/* Populate WrittenBy*/
INSERT INTO WrittenBy(PersonalNo,ISBN)
VALUES	('4529605119','9780131873254'),
	('3192495355','9780131873254'),
	('6447180207','9780131873254'),
	('7552519423','9780132943260'),
	('5868822579','9780132943260');

		
/*  Populate inventory */
INSERT INTO Inventory(SystemNo,ISBN,taken)
VALUES 	('1','9780131873254',false),
	('2','9780131873254',false),
	('3','9780131873254',false),
	('4','9780132943260',false),
	('5','9780132943260',false),
	('6','9780132943260',false);


/* Populate Borrows */
INSERT INTO Borrows(SystemNo,ReaderID,BorrowDate,DueDate,ReturnDate)
VALUES 	('1',1,'2018-06-05','2018-06-25','2018-06-13'),
	('2',2,'2018-06-05','2018-06-25','2018-06-13'),
	('3',1,'2018-06-14','2018-07-03','2018-06-28'),
	('4',1,'2018-03-09','2018-03-29','2018-03-21');

/* Populate Location */
INSERT INTO Location(DepNo,SystemNo)
VALUES 	(1,1),
	(1,2),
	(2,3),
	(1,4),
	(3,5);