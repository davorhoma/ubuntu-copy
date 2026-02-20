#!/bin/sh
echo "Create database migrations"
python3 manage.py makemigrations

echo "Migrate"
python3 manage.py migrate

echo "Run server"
python3 manage.py runserver 0.0.0.0:9000