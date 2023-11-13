package com.reliability.dto;

import lombok.Data;

@Data
public class DataBaseDTO {
    private Type type;
    private String host;
    private String port;
    private String database;
    private String table;
    private String username;
    private String password;
}
