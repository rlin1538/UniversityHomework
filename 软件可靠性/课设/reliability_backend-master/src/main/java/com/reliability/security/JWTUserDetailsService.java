package com.reliability.security;

import com.reliability.exception.CustomException;
import com.reliability.repository.UserRepository;
import org.springframework.http.HttpStatus;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class JWTUserDetailsService implements UserDetailsService {
    // can't use UserService here, which will produce circular dependencies
    private final UserRepository userRepository;

    public JWTUserDetailsService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }


    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        var user = this.userRepository.findByUsername(username);
        if (user == null) {
            throw new CustomException(HttpStatus.BAD_REQUEST, "User Not Found");
        }
        if (user.getIsLocked()) {
            throw new CustomException(HttpStatus.FORBIDDEN, "User account is locked");
        }
        var authority = user.getIsAdmin() ? "ROLE_ADMIN" : "ROLE_USER";
        return User.builder()
                .username(username)
                .password(user.getPassword())
                .authorities(authority)
                .accountExpired(false)
                .accountLocked(user.getIsLocked())
                .credentialsExpired(false)
                .disabled(false)
                .build();
    }
}
