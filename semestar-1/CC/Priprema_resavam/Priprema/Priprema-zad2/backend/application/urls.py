from . import views
from django.urls import path

urlpatterns = [
    path('getGoals', views.get_goals),
    path('newGoal', views.new_goal)
]