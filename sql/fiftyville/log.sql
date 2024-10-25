-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
 Interviews were conducted today with three witnesses who were present at the time –
 each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.

SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;

Ruth
 Sometime within ten minutes of the theft, I saw the thief get into a car
 in the bakery parking lot and drive away. If you have security footage from
 the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
Eugene
 I don't know the thief's name, but it was someone I recognized.
 Earlier this morning, before I arrived at Emma s bakery,
 I was walking by the ATM on Leggett Street and saw the thief
there withdrawing some money.                                                                                                 |
Raymond
 As the thief was leaving the bakery, they called someone who talked
 to them for less than a minute. In the call, I heard the thief say that they were planning
 to take the earliest flight out of Fiftyville tomorrow.
 The thief then asked the person on the other end of the phone to purchase the flight ticket. |


SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021;

+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+


SELECT *
FROM bank_accounts
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021);

+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048    | 2010          |
| 86363979       | 948985    | 2010          |
| 26013199       | 514354    | 2012          |
| 16153065       | 458378    | 2012          |
| 28296815       | 395717    | 2014          |
| 25506511       | 396669    | 2014          |
| 28500762       | 467400    | 2014          |
| 76054385       | 449774    | 2015          |
| 81061156       | 438727    | 2018          |
+----------------+-----------+---------------+

SELECT * FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021);

+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+

+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       | 86363979       | 948985    | 2010          |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       | 458378    | 2012          |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       | 395717    | 2014          |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       | 438727    | 2018          |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+

SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021);

SELECT * FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021));

SELECT * FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021))
AND month = 7 AND day = 28;
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate | account_number | person_id | creation_year |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       | 686048    | 2010          |
| 948985 | Kaelyn  | (098) 555-1164 | 8304650265      | I449449       | 86363979       | 948985    | 2010          |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       | 514354    | 2012          |
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       | 458378    | 2012          |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       | 395717    | 2014          |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       | 396669    | 2014          |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       | 467400    | 2014          |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       | 449774    | 2015          |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       | 438727    | 2018          |
+--------+---------+----------------+-----------------+---------------+----------------+-----------+---------------+
-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
+-----+------+-------+-----+------+--------+----------+---------------+
| id  | year | month | day | hour | minute | activity | license_plate |
+-----+------+-------+-----+------+--------+----------+---------------+
| 231 | 2021 | 7     | 28  | 8    | 18     | entrance | L93JTIZ       |
| 232 | 2021 | 7     | 28  | 8    | 23     | entrance | 94KL13X       |
| 237 | 2021 | 7     | 28  | 8    | 34     | entrance | 1106N58       |
| 240 | 2021 | 7     | 28  | 8    | 36     | entrance | 322W7JE       |
| 254 | 2021 | 7     | 28  | 9    | 14     | entrance | 4328GD8       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
+-----+------+-------+-----+------+--------+----------+---------------+

+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 231 | (801) 555-9266 | (984) 555-5921 | 2021 | 7     | 28  | 148      |
| 232 | (971) 555-6468 | (267) 555-2761 | 2021 | 7     | 28  | 149      |
| 237 | (394) 555-3247 | (035) 555-2997 | 2021 | 7     | 28  | 111      |
| 240 | (636) 555-4198 | (670) 555-8598 | 2021 | 7     | 28  | 69       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 263 | (342) 555-9260 | (487) 555-5865 | 2021 | 7     | 28  | 560      |
| 265 | (398) 555-1013 | (329) 555-5870 | 2021 | 7     | 28  | 237      |
| 266 | (016) 555-9166 | (336) 555-0077 | 2021 | 7     | 28  | 88       |
| 268 | (122) 555-4581 | (831) 555-0973 | 2021 | 7     | 28  | 491      |
+-----+----------------+----------------+------+-------+-----+----------+
+-----+
| id  |
+-----+
| 218 |
| 231 |
| 232 |
| 237 |
| 238 |
| 240 |
| 254 |
| 261 |
| 263 |
| 265 |
| 266 |
| 268 |
| 277 |
+-----+

+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
| 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT name FROM people
WHERE license_plate = '4328GD8';

SELECT * FROM flights
WHERE id in (SELECT id FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021))
AND month = 7 AND day = 28 AND year = 2021)
AND month = 7 AND day = 29 AND year = 2021;



SELECT id FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021))
AND month = 7 AND day = 28;


SELECT * FROM flights
WHERE month = 7 AND day = 28 AND year = 2021;


SELECT * FROM phone_calls
WHERE id in (SELECT id FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021))
AND month = 7 AND day = 28);

SELECT id from phone_calls where receiver in
(SELECT receiver FROM phone_calls
WHERE id in (SELECT id FROM bakery_security_logs
WHERE license_plate in (SELECT license_plate FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND year = 2021))
AND month = 7 AND day = 28))
and month = 7 AND day = 28;


