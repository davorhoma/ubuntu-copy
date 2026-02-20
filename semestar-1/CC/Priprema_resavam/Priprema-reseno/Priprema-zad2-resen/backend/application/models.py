from django.db import models

class Goal(models.Model):
    text = models.CharField(max_length=200)
