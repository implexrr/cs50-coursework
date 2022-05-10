SELECT s.name
FROM songs s, artists a
ON s.artist_id = a.id
AND a.name = 'Post Malone';

/*
SELECT name FROM songs
WHERE artist_id = (
    SELECT id
    FROM artists
    WHERE name = 'Post Malone');
*/