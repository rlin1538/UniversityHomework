package com.reliability.security;

import com.reliability.entity.User;
import io.jsonwebtoken.JwtException;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.io.Decoders;
import io.jsonwebtoken.security.Keys;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.crypto.SecretKey;
import java.util.Date;

@Component
public class JWTUtil {
    @Value("${security.jwt.token.secret-key:secret-key}")
    private String secretKey;

    @Value("${security.jwt.token.expiration:300000}")
    private Long expiration;

    private SecretKey key;

    private final JWTUserDetailsService jwtUserDetailsService;

    private final BCryptPasswordEncoder encoder = new BCryptPasswordEncoder();

    public JWTUtil(JWTUserDetailsService jwtUserDetailsService) {
        this.jwtUserDetailsService = jwtUserDetailsService;
    }

    @PostConstruct
    protected void init() {
        this.key = Keys.hmacShaKeyFor(Decoders.BASE64.decode(secretKey));
    }

    public String generateJWT(User user) {
        return Jwts.builder()
                .setExpiration(new Date(System.currentTimeMillis() + expiration))
                .setSubject(user.getUsername())
                .claim("id", user.getId())
                .signWith(this.key, SignatureAlgorithm.HS256)
                .compact();
    }

    public Authentication getAuthenticationFromToken(String token) {
        if (!token.startsWith("Bearer")) {
            return null;
        }
        String jwt = token.substring(7);
        try {
            var claims = Jwts.parserBuilder()
                    .setSigningKey(this.key)
                    .build()
                    .parseClaimsJws(jwt)
                    .getBody();
            var username = (String) claims.get("sub");
            var userDetails = this.jwtUserDetailsService.loadUserByUsername(username);
            return new UsernamePasswordAuthenticationToken(userDetails, "", userDetails.getAuthorities());
        } catch (JwtException e) {
            return null;
        }
    }

    public String encodePassword(String password) {
        return this.encoder.encode(password);
    }

    public Boolean checkPassword(String rawPassword, String encodedPassword) {
        return this.encoder.matches(rawPassword, encodedPassword);
    }
}
