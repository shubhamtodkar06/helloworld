SELECT title FROM movies
JOIN ratings ON ratings.movie_id = movies.id
JOIN people ON people.id = stars.person_id
JOIN stars ON movies.id = stars.movie_id
WHERE name = 'Chadwick Boseman' ORDER BY rating DESC LIMIT 5 ;