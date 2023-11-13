package com.example.testend.pojo;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import javax.persistence.*;
import javax.persistence.criteria.CriteriaBuilder;

@Entity //实体类
@Table(name = "user")   //对应数据库表名是user
@JsonIgnoreProperties({"handler","hibernateLazyInitializer"})
/*
* 因为是做前后端分离，而前后端数据交互用的是 json 格式。
* 那么 User 对象就会被转换为 json 数据。
* 而本项目使用 jpa 来做实体类的持久化，jpa 默认会使用 hibernate,
* 在 jpa 工作过程中，就会创造代理类来继承 User ，
* 并添加 handler 和 hibernateLazyInitializer 这两个无须 json 化的属性，
* 所以这里需要用 JsonIgnoreProperties 把这两个属性忽略掉。
*/

public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id")

    Integer id;
    String username;
    String password;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
