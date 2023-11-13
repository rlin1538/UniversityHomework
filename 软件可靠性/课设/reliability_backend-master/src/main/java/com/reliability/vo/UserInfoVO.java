package com.reliability.vo;

import com.reliability.entity.User;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class UserInfoVO {
    private Long id;
    private String username;
    private Boolean isAdmin;
    private Boolean isLocked;

    public UserInfoVO(User user) {
        this.id = user.getId();
        this.username = user.getUsername();
        this.isAdmin = user.getIsAdmin();
        this.isLocked = user.getIsLocked();
    }
}
