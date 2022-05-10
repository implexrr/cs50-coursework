.table
.schema
/*
Results:
airports              crime_scene_reports   people
atm_transactions      flights               phone_calls
bakery_security_logs  interviews
bank_accounts         passengers
-----------------------------------------
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
*/


-- First, we took a look at all crime scene reports that occured on Humphery Street. The scene related to the theft of the cs50 duck said the following:
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street';
/*
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time –
each of their interview transcripts mentions the bakery.
Crime has ID 295.
*/

-- We took a look at witness interviews, of which only 3 were relevant:
SELECT * FROM interviews WHERE transcript LIKE '%bakery%';
/*

+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/


-- Based on the tip given by Ruth, we took a look at all license plates belonging to cars that left the bakery between 10:05 and 10:25AM
SELECT * FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute >= 5 AND minute <= 25;
/*
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 258 | 2021 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
| 259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
+-----+------+-------+-----+------+--------+----------+---------------+
*/

/* Combining Ruth's tip with Raymond's, we noticed that the culprit had to be someone who left the bakery between 10:05AM and 10:25AM that also
left on the first flight from fiftyville the next morning. */
SELECT *
FROM people
WHERE (license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND hour = 10
    AND minute >= 5
    AND minute <= 25))
    AND (passport_number IN (SELECT passport_number FROM passengers
    WHERE flight_id IN
    (
        SELECT id
        FROM flights
        WHERE origin_airport_id = 8 AND day = 29 AND hour = 8 AND minute = 20
        ORDER BY day, hour, minute
    )));
/*
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
*/


--Based on Emma's tip, we took a look at all individuals that made a withdrawl on the morning of July 28th from an ATM on Leggett Street:
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street'))
;
/*
T1:
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+

T2 (From earlier query):
People who left the bakery within 10 min of the crime happening that also left town on the first flight the day after
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
*/

--Looking at both T1 and T2, it was clear the suspect was either Bruce (686048) or Luca (467400).

-- Based on Raymond's tip, we decided to look at all phone calls under 60 seconds that took place on 7/28 originating from one of their phone numbers.
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND (caller = '(389) 555-5198' OR caller = '(367) 555-5533');
/*
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      |
| 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      |
| 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       |
+-----+----------------+----------------+------+-------+-----+----------+
*/
-- This singled out Bruce as the suspect, with his accomplice having the number (375) 555-8161

-- To find his accomplice:
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
*/

-- To find the city he fled to:
SELECT city FROM airports WHERE id IN (
    SELECT destination_airport_id FROM flights WHERE origin_airport_id = 8 AND day = 29 ORDER BY hour, minute
    LIMIT 1
);
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
-- Thus culprit = Bruce (686048), accomplice = Robin (864400) and city culprit fled to = NYC.