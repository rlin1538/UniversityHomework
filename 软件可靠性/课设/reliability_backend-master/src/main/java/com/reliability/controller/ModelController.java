package com.reliability.controller;

import com.reliability.service.ModelService;
import com.reliability.vo.ModelVO;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.security.SecurityRequirement;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/model")
public class ModelController {
    private final ModelService modelService;

    public ModelController(ModelService modelService) {
        this.modelService = modelService;
    }

    @GetMapping("/jm/{uuid}")
    @Operation(summary = "jm model", security = @SecurityRequirement(name = "bearerAuth"))
    public ModelVO jm(@PathVariable("uuid") String uuid, @RequestParam("ex") Double ex, @RequestParam("ey") Double ey) {
        return this.modelService.jm(uuid, ex, ey);
    }

    @GetMapping("/go/{uuid}")
    @Operation(summary = "go model", security = @SecurityRequirement(name = "bearerAuth"))
    public ModelVO go(@PathVariable("uuid") String uuid, @RequestParam("zeta") Double zeta) {
        return this.modelService.go(uuid, zeta);
    }

    @GetMapping("/mo/{uuid}")
    @Operation(summary = "mo model", security = @SecurityRequirement(name = "bearerAuth"))
    public ModelVO mo(@PathVariable("uuid") String uuid, @RequestParam("lambda") Double lambda, @RequestParam("zeta") Double zeta) {
        return this.modelService.mo(uuid, lambda, zeta);
    }

    @GetMapping("/bp/{uuid}")
    @Operation(summary = "bp model", security = @SecurityRequirement(name = "bearerAuth"))
    public ModelVO bp(
            @PathVariable("uuid") String uuid,
            @RequestParam("re") Integer re,
            @RequestParam("learnrate") Double learnrate,
            @RequestParam("maxl") Double maxl
    ) {
        return this.modelService.bp(uuid, re, learnrate, maxl);
    }

    @GetMapping("/svm/{uuid}")
    @Operation(summary = "svm model", security = @SecurityRequirement(name = "bearerAuth"))
    public ModelVO svm(@PathVariable("uuid") String uuid) {
        return this.modelService.svm(uuid);
    }
}
