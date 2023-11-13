package com.example.testend.controller;

import com.example.testend.pojo.Course;
import com.example.testend.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class LibraryController {
    @Autowired
    CourseService courseService;

    @CrossOrigin
    @GetMapping("/api/courses")
    public List<Course> list() throws Exception {
        return courseService.list();
    }

    @CrossOrigin
    @PostMapping ("/api/courses")
    public Course addOrUpdate(@RequestBody Course course) throws Exception {
        courseService.addOrUpdate(course);
        System.out.println("AddOrUpdating");
        return course;
    }

    @CrossOrigin
    @PostMapping("/api/delete")
    public void delete(@RequestBody Course course) throws Exception {
        courseService.deleteById(course.getId());
    }

    @CrossOrigin
    @GetMapping("/api/categories/{cid}/courses")
    public List<Course> listByCategory(@PathVariable("cid") int cid) throws Exception {
        if (0 != cid) {
            return courseService.listByCategory(cid);
        }
        else {
            return list();
        }
    }

    @CrossOrigin
    @GetMapping("/api/search")
    public List<Course> searchResult(@RequestParam("keywords") String keywords) {
        // 关键词为空时查询出所有课程
        System.out.println("关键字："+keywords);
        if ("".equals(keywords)) {
            return courseService.list();
        } else {
            return courseService.Search(keywords);
        }
    }

}
