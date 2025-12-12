from django.contrib import admin

from .models import Meetup, Location, Participant

class LocationAdmin(admin.ModelAdmin):
    list_display = ('name', 'address')

# Register your models here.
admin.site.register(Meetup)
admin.site.register(Location, LocationAdmin)
admin.site.register(Participant)


