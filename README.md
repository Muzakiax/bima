# bima -code generator

The purpose of the application is to generate source code for UI form and/or report based on SQL statement.

The application accepts ER diagram from Dia application - an opensource diagramming program from Gnome https://wiki.gnome.org/Apps/Dia
It will parse the file to find out all objects in the diagram : entity ( table ) , attribute ( field ) and relation between entities.

Steps:
1. Import ER diagram
2. Add additional attributes for each entity
3. Define SQL statement and match code template
4. Generate the code

Relationship between entities play important role

For example a SQL statement that contains 2 tables and the relation of those tables is 1 to many ( 1:N ), model for the UI or report will contain 1 part for a header and other part with grid list
