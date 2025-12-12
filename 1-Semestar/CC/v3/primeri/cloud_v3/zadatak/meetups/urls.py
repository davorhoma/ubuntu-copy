from . import views
from django.urls import path


urlpatterns = [
    path('', views.index, name='all-meetups'), # our-domain.com/meetups
    path('getMeetups', views.get_meetups), # our-domain.com/meetups
    path('getLocations', views.get_locations), 
    path('newLocation', views.new_location),
    path('<slug:meetup_slug>/success', views.confirm_registration, name='confirm_registration'),
    path('<slug:meetup_slug>', views.meetup_details, name='meetup-details') #our-domain.com/meetups/<meeting_slug>
]