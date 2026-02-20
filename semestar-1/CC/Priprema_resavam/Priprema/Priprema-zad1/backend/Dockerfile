FROM node
WORKDIR /app
COPY package.json /app
RUN npm install
COPY . .
EXPOSE 80
ENTRYPOINT ["node"]
CMD ["app.js"]