package com.reliability.vo;

import com.reliability.entity.User;
import lombok.Data;
import org.springframework.data.domain.Page;

import java.util.List;
import java.util.stream.Collectors;

@Data
public class UserListVO {
    private long total;
    private long size;
    private long current;
    private List<UserInfoVO> items;

    public UserListVO(Page<User> page) {
        this.total = page.getTotalElements();
        this.size = page.getSize();
        this.current = page.getNumber();
        this.items = page.getContent().stream().map(UserInfoVO::new).collect(Collectors.toList());
    }
}
