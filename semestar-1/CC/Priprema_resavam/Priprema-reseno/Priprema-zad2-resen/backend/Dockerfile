FROM python:3.10

WORKDIR /app

COPY . .

RUN pip install -r requirements.txt

EXPOSE 8081

#CMD python3 manage.py makemigrations && python3 manage.py migrate && python3 manage.py runserver 0.0.0.0:8081

RUN chmod +x /app/skripta.sh

ENTRYPOINT [ "/app/skripta.sh" ]