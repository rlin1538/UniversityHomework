package com.reliability.controller;

import com.reliability.dto.DataBaseDTO;
import com.reliability.dto.TextDTO;
import com.reliability.service.DataService;
import com.reliability.vo.DataRespVO;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.security.SecurityRequirement;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

@RestController
@RequestMapping("/sourceData")
public class DataController {
    private final DataService dataService;

    public DataController(DataService dataService) {
        this.dataService = dataService;
    }

    @PostMapping(value = "/upload", consumes = {MediaType.MULTIPART_FORM_DATA_VALUE})
    @Operation(summary = "upload file", security = @SecurityRequirement(name = "bearerAuth"))
    public DataRespVO Upload(@RequestParam("file") MultipartFile file) {
        return this.dataService.file(file);
    }

    @PostMapping("/text")
    @Operation(summary = "text input", security = @SecurityRequirement(name = "bearerAuth"))
    public DataRespVO Text(@RequestBody TextDTO textDTO) {
        return this.dataService.text(textDTO);
    }

    @PostMapping("/db")
    @Operation(summary = "db input", security = @SecurityRequirement(name = "bearerAuth"))
    public DataRespVO DB(@RequestBody DataBaseDTO dataBaseDTO) {
        return this.dataService.db(dataBaseDTO);
    }
}
