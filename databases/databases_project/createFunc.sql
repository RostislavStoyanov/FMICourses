set schema 'fn45244';

/* ---- FUNCTION DEFINITIONS ---- */

DROP FUNCTION IF EXISTS MOST_READ;

CREATE FUNCTION MOST_READ ()
/**
            summary:
            This function returns the ISBN of the book that has been rented the most.            
            **/
RETURNS VARCHAR(13) AS $$
	(SELECT ISBN
	FROM Book
	WHERE ISBN =
			(SELECT ISBN
			FROM Inventory i
			JOIN Borrows b ON i.SystemNo = b.SystemNo
			GROUP BY ISBN
			HAVING COUNT(i.SystemNo) >= ALL
				(SELECT COUNT(i1.SystemNo)
		FROM Inventory i1
		JOIN Borrows b1 ON i1.SystemNo = b1.SystemNo
		GROUP BY ISBN)));
$$ LANGUAGE SQL;


DROP FUNCTION IF EXISTS REGISTER_PERSON;

CREATE FUNCTION REGISTER_PERSON(pNo CHAR(10),rID INT)
/**
            summary:
            This function registers a existing person as a reader. Takes 2 parameters - personNo and rID.            
            **/
RETURNS BOOLEAN AS $$
DECLARE
	currDate DATE;
	yearAway DATE;
BEGIN
	currDate := CURRENT_DATE;
	yearAway := currDate + interval '1 year';
	
	IF EXISTS (SELECT 1 FROM Reader WHERE ReaderID = rID)
	THEN 	
		RAISE unique_violation USING MESSAGE = 'Reader already exists';
		RETURN FALSE;
	END IF;
	
	IF NOT EXISTS (SELECT 1 FROM Person WHERE PersonalNo = pNo)
	THEN 
		RAISE unique_violation USING MESSAGE = 'Person doesnt exist';
		RETURN FALSE;
	END IF;
	
	INSERT INTO Reader(ReaderID,RegistrationDate,ExpirationDate)
	VALUES(rID,currDate,yearAway);
	INSERT INTO Registered(PersonalNo,ReaderID)
	VALUES (pNo,rID);
	RETURN TRUE;
END
$$ LANGUAGE plpgsql;


CREATE OR REPLACE FUNCTION DEP_CONTAINS_ISBN(bISBN VARCHAR(13),depNumber INT)
/**
            summary:
            This function checks if a book with the given isbn can be found in the given department            
            **/
RETURNS BOOLEAN AS $$
BEGIN
	IF NOT EXISTS (SELECT 1 FROM Inventory WHERE ISBN = bISBN)
	THEN
		RAISE unique_violation USING MESSAGE = 'No book with that isbn in inventory';
		RETURN FALSE;
	END IF;
	
	IF NOT EXISTS (SELECT 1 FROM Department WHERE depNo = depNumber)
	THEN
		RAISE unique_violation USING MESSAGE = 'No such department exists';
		RETURN FALSE;
	END IF;
	
	RETURN EXISTS (SELECT 1 
				FROM Location l JOIN Inventory i on l.SystemNo = i.SystemNo 
				WHERE i.ISBN = bISBN and l.depNo = depNumber AND i.Taken = FALSE);
END 
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION BORROW_BOOK(rID INT,bISBN VARCHAR(13),depNumber INT)
/**
            summary:
            This function borrows a book(if possible) and returns its systemNo             
            **/
RETURNS VARCHAR(255) AS $$
DECLARE
	currDate DATE;
	returnDate DATE;
	sysNo VARCHAR(255);
BEGIN
	currDate := CURRENT_DATE;
	returnDate := currDate + interval '20 days';

	IF NOT EXISTS (SELECT 1 FROM Reader WHERE ReaderID = rID)
	THEN 
		RAISE unique_violation USING MESSAGE = 'No such reader';
		RETURN NULL;
	END IF;
	
	IF (SELECT 1 FROM DEP_CONTAINS_ISBN(bISBN,depNumber))
	THEN
		sysNo := (SELECT l.SystemNo 
				FROM Location l JOIN Inventory i on l.SystemNo = i.SystemNo
				WHERE i.ISBN = bISBN and l.depNo = depNumber AND i.Taken = FALSE
				limit 10);
		INSERT INTO Borrows(ReaderID,SystemNo,BorrowDate,DueDate,ReturnDate)
		VALUES(rID,sysNo,currDate,returnDate,NULL);
		RETURN sysNo;
	END IF;
	RETURN NULL;
END
$$ LANGUAGE plpgsql;

/* ---- FUNCTION TESTS ---- */


/* Test MOST_READ function using anonymous block the data inserted using the dataLoad.sql*/

DO $$
BEGIN
	IF EXISTS (SELECT 1 FROM 
			(
				SELECT ISBN
				FROM Book WHERE
				ISBN <> '9780131873254' AND ISBN = MOST_READ()
			) AS T
			)
	THEN RAISE unique_violation USING MESSAGE = 'Error when testing MOST_READ';
END IF;
END $$;

SELECT * FROM Book WHERE ISBN = MOST_READ();

/* Test REGISTER_PERSON function using anonymous block and the data inserted using the dataLoad.sql
	Try to raise all possible exceptions and to add one of the librarians to the readers*/
	
/* Throw reader already exists */
SELECT register_person('9514780291',2);

/* Throw person doesnt exist */
SELECT register_person('0000000000',4);

SELECT * FROM READER;
SELECT register_person('8617995849',3);
SELECT * FROM READER;

/* Test dep_contains_isbn */
SELECT dep_contains_isbn('9780131873254',1);
SELECT dep_contains_isbn('0000000000000',1);

/* Test borrow book */
SELECT borrow_book(1,'9780132943260',1);



