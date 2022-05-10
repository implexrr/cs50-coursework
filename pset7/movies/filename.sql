SELECT name FROM people WHERE id IN (
SELECT DISTINCT s1.person_id
FROM stars s1, stars s2
ON s1.movie_id = s2.movie_id
AND s2.person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = '1958')
AND NOT(s1.person_id = s2.person_id)
);