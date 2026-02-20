
import json
from django.http import HttpResponse, JsonResponse
from django.shortcuts import redirect, render
from django.views.decorators.csrf import csrf_exempt

from meetups.serializers import LocationSerializer
from .models import Location, Meetup, Participant
from .forms import RegistrationForm

# Create your views here.
def index(request):
    meetups = Meetup.objects.all()
    return render(request, 'meetups/index.html', {
        'show_meetups' : True,
        'meetups' : meetups
    })

def meetup_details(request, meetup_slug):
    try:
        selected_meetup = Meetup.objects.get(slug=meetup_slug)
        print(selected_meetup.slug)

        if request.method == 'GET':            
            registration_form = RegistrationForm()
            
        else:
            print(request.body)
            registration_form = RegistrationForm(request.POST)
            if registration_form.is_valid():
                user_email = registration_form.cleaned_data['email']
                participant, _ = Participant.objects.get_or_create(email=user_email)
                selected_meetup.participants.add(participant)
                return redirect('confirm_registration', meetup_slug=meetup_slug)

        return render(request, 'meetups/meetup-details.html',{
                'meetup_found':True,
                'meetup':selected_meetup,
                'form':registration_form
            })

    except Exception as exc:
        
        return render(request, 'meetups/meetup-details.html', {
            'meetup_found':False
        })


def confirm_registration(request, meetup_slug):
    meetup = Meetup.objects.get(slug=meetup_slug)
    
    return render(request, 'meetups/registration-success.html', {
        'organizer_email':meetup.organizer_email
    })

def get_meetups(request):
    meetup = Meetup.objects.all().values()   
    meetup_list = list(meetup)
    return JsonResponse(meetup_list , safe=False)

def get_locations(request):
    location = Location.objects.all()
    location_list = LocationSerializer(location,many=True)
    return JsonResponse(location_list.data, safe=False)

@csrf_exempt
def new_location(request):
    data = json.loads(request.body)
    Location.objects.create(name=data['name'], address=data['address'])
    return HttpResponse(status=200)

