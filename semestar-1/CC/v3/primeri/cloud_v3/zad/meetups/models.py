from datetime import date
from distutils.command.upload import upload
from enum import unique
from pydoc import describe
from unicodedata import name
from unittest.util import _MAX_LENGTH
from django.db import models

# Create your models here.

class Location(models.Model):
    name = models.CharField(max_length=200)
    address = models.CharField(max_length=300)

    def __str__(self):
        return f'{self.name} - {self.address}'

class Participant(models.Model):
    email = models.EmailField(unique=True)

class Meetup(models.Model):
    title = models.CharField(max_length=200)
    organizer_email = models.EmailField()
    date = models.DateField()
    slug = models.SlugField(unique=True)
    description = models.TextField()
    image = models.ImageField(upload_to='images')
    location = models.ForeignKey(Location, on_delete=models.CASCADE)
    participants = models.ManyToManyField(Participant, blank=True, null=True)
     