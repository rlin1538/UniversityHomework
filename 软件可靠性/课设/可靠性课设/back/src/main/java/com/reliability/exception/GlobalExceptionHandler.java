package com.reliability.exception;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.http.HttpStatus;
import org.springframework.security.access.AccessDeniedException;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import javax.servlet.http.HttpServletResponse;

@RestControllerAdvice
public class GlobalExceptionHandler {
    @ExceptionHandler(CustomException.class)
    public ErrorResponse handleCustomException(HttpServletResponse res, CustomException e) {
        res.setStatus(e.getHttpStatus().value());
        return new ErrorResponse(e.getHttpStatus().value(), e.getMessage());
    }

    @ExceptionHandler(BadCredentialsException.class)
    public ErrorResponse handleBadCredentialsException(HttpServletResponse res) {
        res.setStatus(HttpStatus.UNPROCESSABLE_ENTITY.value());
        return new ErrorResponse(HttpStatus.UNPROCESSABLE_ENTITY.value(), "password incorrect");
    }

    @ExceptionHandler(AccessDeniedException.class)
    public ErrorResponse handleAccessDeniedException(HttpServletResponse res) {
        res.setStatus(HttpStatus.FORBIDDEN.value());
        return new ErrorResponse(HttpStatus.FORBIDDEN.value(), "access denied");
    }
}

@Data
@AllArgsConstructor
class ErrorResponse {
    private Integer status;
    private String message;
}
