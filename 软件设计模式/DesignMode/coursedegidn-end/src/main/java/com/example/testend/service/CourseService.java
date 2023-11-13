package com.example.testend.service;

import com.example.testend.dao.CourseDAO;
import com.example.testend.pojo.Course;
import com.example.testend.pojo.Category;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CourseService {

    @Autowired
    CourseDAO courseDAO;
    @Autowired
    CategoryService categoryService;

    public List<Course> list() {
        Sort sort = new Sort(Sort.Direction.DESC,"id");
        return courseDAO.findAll(sort);
    }

    public List<Course> Search(String keywords) {
        return courseDAO.findAllByNameLikeOrCodeLike('%' + keywords + '%','%'+ keywords + '%');
    }
    public void addOrUpdate(Course course) {
        courseDAO.save(course);
        //这里注意一下 save() 方法的作用是，当主键存在时更新数据，当主键不存在时插入数据。
        //
        //这也就是核心的业务逻辑了。
    }

    public void deleteById(int id) {
        courseDAO.deleteById(id);
    }

    public List<Course> listByCategory(int cid) {
        Category category = categoryService.get(cid);
        return courseDAO.findAllByCategory(category);
    }
}
