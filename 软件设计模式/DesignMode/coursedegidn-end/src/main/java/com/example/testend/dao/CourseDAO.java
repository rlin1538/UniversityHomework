package com.example.testend.dao;

import com.example.testend.pojo.Course;
import com.example.testend.pojo.Category;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface CourseDAO extends JpaRepository<Course,Integer> {
    List<Course> findAllByCategory(Category category);
    List<Course> findAllByNameLikeOrCodeLike(String keyword1, String keyword2);

}
