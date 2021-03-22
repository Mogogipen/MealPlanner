-- placeholder variables
SET rID = 1;
SET iID = 1;

-- Get a recipe with a specific id
SELECT * FROM recipe WHERE idrecipe = rID;

-- Get all recipes
SELECT * FROM recipe;

-- Get all ingredients associated with a recipe
SELECT name, ingQty
	FROM ingredient, recipe_has_ingredient
	WHERE idingredient = ingredient_idingredient AND recipe_idrecipe = rID;

-- Add a new recipe
INSERT INTO mydb.recipe (title, author, instructions) VALUES ('<Title>', '<Author>', '<Instructions>');
INSERT INTO mydb.recipe_has_ingredient (recipe_idrecipe, ingredient_idingredient, ingQty) VALUES (rID, iID, '<qty>'); -- to be used for each ingredient

-- Alter recipe with a specific id
UPDATE mydb.recipe SET title = '<Title>', author = '<Author>', instructions = '<Instructions>' WHERE (idrecipe = rID);
DELETE FROM mydb.recipe_has_ingredient WHERE recipe_idrecipe = rID AND ingredient_idingredient = iID; -- to be used for each ingredient
INSERT INTO mydb.recipe_has_ingredient (recipe_idrecipe, ingredient_idingredient, ingQty) VALUES (rID, iID, '<qty>'); -- to be used for each ingredient

-- Remove a recipe
DELETE FROM mydb.recipe WHERE id = rID;
DELETE FROM mydb.recipe_has_ingredient WHERE recipe_idrecipe = rID;

--
-- Add a new ingredient
INSERT INTO mydb.ingredient (name) VALUES ('<Name>');

-- Get all ingredients
SELECT * FROM ingredient;

-- Delete all unused ingredients
DELETE FROM mydb.ingredient
	WHERE idingredient NOT IN (SELECT ingredient_idingredient FROM recipe_has_ingredient);

-- Get all unique ingredients used in recipes with specific ids
SELECT idingredient, name
	FROM ingredient, recipe_has_ingredient
    WHERE (recipe_idrecipe) IN (1, 4) AND ingredient_idingredient = idingredient
    GROUP BY idingredient;
