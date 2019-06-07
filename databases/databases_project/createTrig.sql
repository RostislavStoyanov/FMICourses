set schema 'fn45244';

CREATE OR REPLACE FUNCTION funInsBorrow() RETURNS trigger AS
$$
BEGIN
	UPDATE Inventory
	SET Taken = TRUE
	WHERE SystemNo = NEW.SystemNo;
	RETURN NEW;
END
$$ LANGUAGE PLPGSQL;

DROP TRIGGER IF EXISTS trigger_ins_borrow ON Borrows;

CREATE TRIGGER trigger_ins_borrow
AFTER INSERT 
ON Borrows
FOR EACH ROW EXECUTE PROCEDURE funInsBorrow();


CREATE OR REPLACE FUNCTION insBookPublisher() RETURNS trigger AS
$$
BEGIN
	IF NOT EXISTS (SELECT 1 FROM Publisher
					WHERE PublisherID = NEW.PublisherID)
	THEN INSERT INTO Publisher(Name,Address)
	VALUES (NULL,NULL);
	END IF;
	RETURN NEW;
END
$$ LANGUAGE PLPGSQL;

DROP TRIGGER IF EXISTS trigger_publisher_book ON Book;

CREATE TRIGGER trigger_del_book
BEFORE INSERT
ON Book
EXECUTE PROCEDURE insBookPublisher();

/* TESTS */

SELECT * FROM Inventory WHERE Taken = TRUE;
INSERT INTO Borrows
VALUES ('1',1,'2019-05-07','2018-05-27',NULL);
SELECT * FROM Inventory WHERE Taken = TRUE;

SELECT * FROM Publisher;
INSERT INTO Book
VALUES('9780073523323','Database System Concepts',1376,6,'Paperback',2,'2010-01-27');
SELECT * FROM Publisher;