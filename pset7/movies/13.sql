/*
In 13.sql, write a SQL query to list the names of all people who starred in a movie
in which Kevin Bacon also starred.
Your query should output a table with a single column for the name of each person.
There may be multiple people named Kevin Bacon in the database. Be sure to only
select the Kevin Bacon born in 1958.
Kevin Bacon himself should not be included in the resulting list.
*/

SELECT name
FROM people
WHERE id
IN
(
    SELECT DISTINCT s1.person_id
    FROM stars s1, stars s2
        ON s1.movie_id = s2.movie_id
        AND s2.person_id =
        (
            SELECT id
            FROM people
            WHERE name = 'Kevin Bacon'
                AND birth = '1958'
        )
                AND NOT
                (
                    s1.person_id = s2.person_id
                )
);