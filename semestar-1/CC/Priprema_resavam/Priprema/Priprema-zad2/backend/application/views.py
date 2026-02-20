from django.shortcuts import render

# Create your views here.

import json
from django.http import HttpResponse, JsonResponse
from django.shortcuts import render
from .models import Goal
from django.views.decorators.csrf import csrf_exempt

def get_goals(request):
    goals = Goal.objects.all().values()
    goal_list = list(goals)
    return JsonResponse(goal_list, safe=False)

@csrf_exempt
def new_goal(request):
    data = json.loads(request.body)
    Goal.objects.create(text=data['text'])
    return HttpResponse(status=200)