package com.reliability.controller;

import com.reliability.dto.UserDataDTO;
import com.reliability.service.UserService;
import com.reliability.vo.TokenVO;
import com.reliability.vo.UserInfoVO;
import org.modelmapper.ModelMapper;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/auth")
public class AuthController {
    private final ModelMapper modelMapper;
    private final UserService userService;

    public AuthController(ModelMapper modelMapper, UserService userService) {
        this.modelMapper = modelMapper;
        this.userService = userService;
    }

    @PostMapping("/register")
    public UserInfoVO register(@RequestBody UserDataDTO registerUser) {
        var user = this.userService.register(registerUser);
        return this.modelMapper.map(user, UserInfoVO.class);
    }

    @PostMapping("/login")
    public TokenVO login(@RequestBody UserDataDTO loginUser){
        return new TokenVO(this.userService.login(loginUser));
    }
}
