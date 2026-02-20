package com.example.demo.service;

import com.example.demo.model.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.concurrent.TimeUnit;

@Service
public class UserService {
    @Autowired
    private RedisTemplate<String, User> redisTemplate;

    private static final String USER_CACHE_PREFIX = "user:";

    public User getUserById(String id) {
        // Pokušaj da pročitaš korisnika iz keša
        User user = redisTemplate.opsForValue().get(USER_CACHE_PREFIX + id);

        if (user != null) {
            System.out.println("Fetching from Redis Cache");
            return user;
        }

        // Ako korisnik nije u kešu, simuliramo da ga tražimo iz baze
        System.out.println("Fetching from Database");
        user = new User();
        user.setId(id);
        user.setName("John Doe");
        user.setEmail("john.doe@example.com");

        // Sačuvaj korisnika u Redis kešu (ističe za 10 minuta)
        redisTemplate.opsForValue().set(USER_CACHE_PREFIX + id, user, 10, TimeUnit.MINUTES);

        return user;
    }
}
