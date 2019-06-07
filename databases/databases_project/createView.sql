set schema 'fn45244';

CREATE OR REPLACE VIEW not_returned AS
	SELECT r.ReaderID as Reader, b.SystemNo as BookNo ,b.DueDate as ReturnDate
	FROM Reader r join Borrows b on b.ReaderID = r.ReaderID
	JOIN (SELECT * FROM Inventory WHERE taken = true) as i 
	ON i.SystemNo = b.SystemNo;
	
	
CREATE OR REPLACE VIEW authorsBooks AS
	SELECT b.ISBN,b.Title,p.Name FROM Book b
	INNER JOIN WrittenBy w on b.ISBN = w.ISBN 
	INNER JOIN Person p on p.PersonalNo = w.PersonalNo;
	


CREATE OR REPLACE VIEW publisher_books AS
	SELECT b.ISBN,b.Title,p.Name,b.PublishDate FROM Book b
	INNER JOIN Publisher p on p.PublisherID = b.PublisherID;

/* TESTS */

SELECT * FROM not_returned;

SELECT * FROM authorsbooks;

SELECT * FROM publisher_books;