package com.reliability.controller;

import com.reliability.dto.PageDTO;
import com.reliability.repository.UserRepository;
import com.reliability.service.UserService;
import com.reliability.vo.UserInfoVO;
import com.reliability.vo.UserListVO;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.security.SecurityRequirement;
import org.modelmapper.ModelMapper;
import org.springframework.data.domain.PageRequest;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/users")
public class UserController {
    private final UserRepository userRepository;
    private final UserService userService;
    private final ModelMapper modelMapper;

    public UserController(UserRepository userRepository, UserService userService, ModelMapper modelMapper) {
        this.userRepository = userRepository;
        this.userService = userService;
        this.modelMapper = modelMapper;
    }

    @GetMapping("/")
    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @Operation(summary = "get user list", security = @SecurityRequirement(name = "bearerAuth"))
    public UserListVO getUserList(PageDTO pageDTO) {
        var pageable = PageRequest.of(pageDTO.getPage(), pageDTO.getSize());
        var users = this.userRepository.findAll(pageable);
        return new UserListVO(users);
    }

    @GetMapping("/me")
    @Operation(summary = "show the login user's detail", security = @SecurityRequirement(name = "bearerAuth"))
    public UserInfoVO getMe() {
        return modelMapper.map(this.userService.getMe(), UserInfoVO.class);
    }
}
