FROM maven:3.8.8-eclipse-temurin-17 AS build
WORKDIR /app
COPY . .
RUN mvn clean package -DskipTests

FROM eclipse-temurin:17-jdk-alpine
WORKDIR /app
COPY --from=build /app/target/demo-0.0.1-SNAPSHOT.jar .
EXPOSE 8000
ENTRYPOINT ["java", "-jar", "demo-0.0.1-SNAPSHOT.jar"]