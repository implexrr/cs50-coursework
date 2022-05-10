SELECT AVG(songs.energy)
FROM songs, artists
ON songs.artist_id = artists.ID
WHERE artists.name = 'Drake';

/*
SELECT AVG(energy) FROM songs
WHERE artist_id = (
    SELECT id FROM artists
    WHERE name == 'Drake');
0.599 = result
*/