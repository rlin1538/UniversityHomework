package com.example.testend.controller;

import com.example.testend.result.Result;
import com.example.testend.pojo.User;
import com.example.testend.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.util.HtmlUtils;
import java.util.Objects;

@Controller
public class LoginController {

    @Autowired
    UserService userService;

    @CrossOrigin
    @PostMapping(value = "api/login")
    @ResponseBody
    public Result login(@RequestBody User requestUser){
        String username = requestUser.getUsername();
        //username = HtmlUtils.htmlEscape(username);
        // 对 html 标签进行转义，防止 XSS 攻击

        /*if (!Objects.equals("admin",username) || !Objects.equals("123456",requestUser.getPassword())) {
            String message = "帐号密码错误";
            System.out.println("test");
            return new Result(400);
        } else  {
            return new Result(200);
        }*/
        User user = userService.get(username,requestUser.getPassword());
        if (null == user)
            return new Result(400);
        else
            return new Result(200);
    }
}
