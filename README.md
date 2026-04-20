# Dynamic Social Media Data Visualization Platform

A full-stack web application that transforms raw social media data into interactive, customizable visualizations. Built with modern web technologies to demonstrate data engineering and visualization skills.

## 🚀 Project Overview

This project showcases my ability to build end-to-end data applications, from database design to interactive web interfaces. I created a dynamic visualization platform that allows users to explore social media analytics data through custom charts and insights.

## 🛠️ Tech Stack

**Backend:**
- **FastAPI** - High-performance async web framework
- **SQLAlchemy** - ORM for database operations
- **Pandas & NumPy** - Data processing and analysis
- **MySQL** - Relational database management

**Frontend:**
- **HTML5/CSS3** - Responsive web design
- **Bootstrap 5** - Modern UI components
- **Chart.js** - Interactive data visualizations
- **Vanilla JavaScript** - Dynamic user interactions

## ✨ Key Features

### 🎯 Dynamic Visualization Engine
- **8 Data Tables**: User demographics, account metrics, activity patterns, health profiles, work data, lifestyle habits, and security settings
- **6 Chart Types**: Bar, Line, Pie, Doughnut, Scatter, and Radar charts
- **Flexible Query Builder**: Users can select any combination of data fields and aggregation methods
- **Advanced Filtering**: Support for multiple filter conditions with various operators

### 📊 Data Processing Pipeline
- **Automated Data Cleaning**: Handles missing values, outliers, and data normalization
- **Real-time Statistics**: Calculates and displays key metrics for each visualization
- **Type Safety**: Proper data validation and error handling throughout the application

### 🎨 Interactive Web Interface
- **Responsive Design**: Works seamlessly across desktop and mobile devices
- **Real-time Updates**: Instant chart generation without page refreshes
- **Error Handling**: User-friendly error messages and loading states
- **Data Tables**: Raw data preview for transparency

## 🔧 Technical Implementation

### Database Architecture
Designed a normalized MySQL schema with proper relationships and constraints:
- User profiles with demographic information
- Activity tracking for social media engagement
- Health and lifestyle data integration
- Account management and security settings

### API Design
Built RESTful endpoints with FastAPI:
- Dynamic query generation based on user parameters
- Input validation and sanitization
- Efficient data retrieval and processing
- Comprehensive error responses

### Frontend Architecture
Created a single-page application with:
- Modular JavaScript functions for different features
- Asynchronous data fetching and rendering
- Chart.js integration for multiple visualization types
- Bootstrap components for consistent UI

## 📈 Learning Outcomes

Through this project, I gained hands-on experience with:

- **Full-Stack Development**: From database design to user interface
- **Data Engineering**: ETL processes, data cleaning, and transformation
- **API Development**: RESTful design and asynchronous programming
- **Frontend Technologies**: Modern JavaScript and responsive design
- **Problem Solving**: Handling complex user requirements and edge cases
- **Performance Optimization**: Efficient data processing and rendering

## 🚀 Getting Started

### Prerequisites
- Python 3.8+
- MySQL Server
- Modern web browser

### Installation

1. **Clone and setup environment:**
```bash
git clone <repository-url>
cd dynamic-social-media-visualization
pip install -r requirements.txt
```

2. **Database setup:**
```bash
mysql -u root -p < Tables.sql
```

3. **Data processing:**
```bash
python Connetor.py
```

4. **Launch application:**
```bash
uvicorn main:app --reload
```

5. **Access the application:**
Open `http://localhost:8000` in your browser

## 🎯 Usage Examples

### Creating Visualizations
1. Select a data table (e.g., "user demographics")
2. Choose chart type (e.g., "Bar Chart")
3. Pick X-axis field (e.g., "gender")
4. Select Y-axis field and aggregation (e.g., "age" with "AVG")
5. Add optional filters (e.g., age > 25)
6. Generate and explore your custom visualization!

### Sample Visualizations
- User engagement patterns by location
- Health metrics distribution
- Activity trends over time
- Demographic breakdowns
- Lifestyle correlations

## 🔍 Code Quality

- **Clean Architecture**: Separation of concerns between data, business logic, and presentation layers
- **Error Handling**: Comprehensive exception handling and user feedback
- **Documentation**: Clear docstrings and inline comments for maintainability
- **Performance**: Optimized database queries and efficient data processing
- **Security**: Input validation and SQL injection prevention

## 🎓 Academic Context

This project was developed as part of my data science and web development coursework. It demonstrates practical application of concepts learned in:

- Database Management Systems
- Web Application Development
- Data Analysis and Visualization
- Software Engineering Principles
- User Experience Design

## 📈 Future Enhancements

Potential improvements for continued development:
- User authentication and personalized dashboards
- Advanced statistical analysis features
- Export functionality for charts and data
- Real-time data streaming capabilities
- Machine learning insights integration

## 🤝 Contributing

This project represents my individual learning journey, but I'm always open to feedback and suggestions for improvement!

---

**Built with passion for data and beautiful user experiences** ✨</content>
<parameter name="filePath">c:\Users\surface\Downloads\Assignment2\README.md