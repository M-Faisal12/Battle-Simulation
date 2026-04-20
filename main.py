from fastapi import FastAPI, HTTPException, Request
from fastapi.staticfiles import StaticFiles
from fastapi.responses import HTMLResponse, FileResponse
from sqlalchemy import create_engine, text
import pandas as pd
import numpy as np
import json
from pathlib import Path
from typing import Optional

app = FastAPI(title="Dynamic Social Media Data Visualization")

engine = create_engine("mysql+mysqlconnector://root:123456@localhost/socialmedia")

TABLE_SCHEMA = {
    "user": ["userid", "age", "gender", "urban_rural", "relationship_status", "has_children", "country"],
    "mentalprofile": ["userid", "self_reported_happiness", "perceived_stress_score"],
    "healthprofile": ["userid", "systolicbp", "diastolicbp", "body_mass_index", "sleep_hours_per_night", "diet_quality"],
    "workprofile": ["userid", "income_level", "employment_status", "weekly_work_hours"],
    "lifestyleprofile": ["userid", "travel_freq_per_year", "books_read_per_year", "social_events_per_month", "hobbies_count", "volunteer_hours_per_month"],
    "account": ["accountid", "userid", "follows_count", "following_count", "user_premium", "account_creation_date", "last_login_date", "average_session_length", "linked_accounts_count", "subscription_status", "user_engagement_score", "notification_response_rate", "preferred_content_theme", "content_type_preference", "sessions_per_day"],
    "securitysettings": ["accountid", "two_factor_auth_enabled", "biometric_login_enabled", "privacy_setting"],
    "instaactivity": ["activityid", "userid", "posts_created_per_week", "reels_watched_per_day", "stories_viewed_per_day", "likes_given_per_day", "comments_made_per_day", "time_on_message_per_day", "dms_sent_per_week", "dms_received_per_week", "daily_active_minutes", "ads_clicked_per_day", "ads_viewed_per_day", "time_on_reels_per_day", "time_on_explore_per_day", "time_on_feed_per_day"]
}

def clean_dataframe(df):
    """Clean and prepare dataframe for analysis"""
    df = df.drop_duplicates()

    numeric_cols = df.select_dtypes(include=[np.number]).columns
    df[numeric_cols] = df[numeric_cols].fillna(df[numeric_cols].mean())

    object_cols = df.select_dtypes(include=['object']).columns
    df[object_cols] = df[object_cols].fillna('Unknown')

    for col in numeric_cols:
        if df[col].std() > 0:
            mean = df[col].mean()
            std = df[col].std()
            df[col] = df[col].where((df[col] - mean).abs() <= 3 * std, mean)

    
    object_cols = df.select_dtypes(include=['object']).columns
    df[object_cols] = df[object_cols].fillna('Unknown')
    
    # Remove outliers (values beyond 3 standard deviations)
    for col in numeric_cols:
        if df[col].std() > 0:
            mean = df[col].mean()
            std = df[col].std()
            df[col] = df[col].where((df[col] - mean).abs() <= 3 * std, mean)
    
    return df

@app.get("/", response_class=HTMLResponse)
def root():
    """Dynamic visualization dashboard"""
    html = """
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title>Dynamic Social Media Data Visualization</title>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
        <style>
            body {
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                min-height: 100vh;
                padding: 20px;
            }
            .container-main {
                background: white;
                border-radius: 15px;
                box-shadow: 0 10px 40px rgba(0,0,0,0.3);
                padding: 30px;
                margin-bottom: 30px;
            }
            .header {
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white;
                padding: 30px;
                border-radius: 10px;
                margin-bottom: 30px;
                text-align: center;
            }
            .card-custom {
                border: none;
                border-radius: 10px;
                box-shadow: 0 5px 15px rgba(0,0,0,0.1);
                transition: transform 0.3s;
            }
            .card-custom:hover {
                transform: translateY(-5px);
            }
            .btn-custom {
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                border: none;
                color: white;
                border-radius: 5px;
                padding: 10px 20px;
                cursor: pointer;
                transition: all 0.3s;
            }
            .btn-custom:hover {
                transform: scale(1.05);
            }
            .form-control:focus {
                border-color: #667eea;
                box-shadow: 0 0 0 0.2rem rgba(102, 126, 234, 0.25);
            }
        </style>
    </head>
    <body>
        <div class="container-main">
            <div class="header">
                <h1>📊 Dynamic Data Visualization</h1>
                <p>Create custom visualizations from your social media data</p>
            </div>

            <div class="row mb-4">
                <div class="col-md-3">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">📋 Select Table</h6>
                            <select id="table-select" class="form-select" onchange="updateColumns()">
                                <option value="">Choose a table...</option>
                                <option value="user">User Demographics</option>
                                <option value="account">Account Data</option>
                                <option value="instaactivity">Instagram Activity</option>
                                <option value="mentalprofile">Mental Health</option>
                                <option value="healthprofile">Health Profile</option>
                                <option value="workprofile">Work Profile</option>
                                <option value="lifestyleprofile">Lifestyle</option>
                                <option value="securitysettings">Security Settings</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="col-md-3">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">📊 Chart Type</h6>
                            <select id="chart-type" class="form-select">
                                <option value="bar">Bar Chart</option>
                                <option value="line">Line Chart</option>
                                <option value="pie">Pie Chart</option>
                                <option value="doughnut">Doughnut Chart</option>
                                <option value="scatter">Scatter Plot</option>
                                <option value="radar">Radar Chart</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="col-md-3">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">📈 X-Axis (Category)</h6>
                            <select id="x-axis" class="form-select">
                                <option value="">Select column...</option>
                            </select>
                        </div>
                    </div>
                </div>

                <div class="col-md-3">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">📊 Y-Axis (Value)</h6>
                            <select id="y-axis" class="form-select">
                                <option value="">Select column...</option>
                            </select>
                            <select id="aggregation" class="form-select mt-2">
                                <option value="COUNT">Count</option>
                                <option value="SUM">Sum</option>
                                <option value="AVG">Average</option>
                                <option value="MIN">Minimum</option>
                                <option value="MAX">Maximum</option>
                            </select>
                        </div>
                    </div>
                </div>
            </div>

            <div class="row mb-4">
                <div class="col-md-6">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">🔍 Filters (Optional)</h6>
                            <div class="row">
                                <div class="col-4">
                                    <select id="filter-column" class="form-select">
                                        <option value="">Column</option>
                                    </select>
                                </div>
                                <div class="col-3">
                                    <select id="filter-operator" class="form-select">
                                        <option value="=">=</option>
                                        <option value="!=">!=</option>
                                        <option value=">">></option>
                                        <option value="<"><</option>
                                        <option value=">=">>=</option>
                                        <option value="<="><=</option>
                                        <option value="LIKE">Contains</option>
                                    </select>
                                </div>
                                <div class="col-5">
                                    <input type="text" id="filter-value" class="form-control" placeholder="Value">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col-md-6">
                    <div class="card card-custom">
                        <div class="card-body">
                            <h6 class="card-title">📝 Chart Title</h6>
                            <input type="text" id="chart-title" class="form-control" placeholder="Enter chart title..." value="Custom Data Visualization">
                        </div>
                    </div>
                </div>
            </div>

            <div class="text-center mb-4">
                <button class="btn btn-custom btn-lg me-3" onclick="generateVisualization()">
                    🎨 Generate Visualization
                </button>
                <button class="btn btn-outline-secondary btn-lg" onclick="clearVisualization()">
                    🗑️ Clear
                </button>
            </div>

            <div id="loading-spinner" class="text-center d-none">
                <div class="spinner-border text-primary" role="status">
                    <span class="visually-hidden">Loading...</span>
                </div>
                <p class="mt-2">Generating your visualization...</p>
            </div>

            <div id="visualization-container" class="mt-5">
                <div class="row">
                    <div class="col-md-8">
                        <canvas id="chartCanvas"></canvas>
                    </div>
                    <div class="col-md-4">
                        <div id="stats-container"></div>
                    </div>
                </div>
                <div id="table-container" class="mt-4"></div>
            </div>

            <div id="error-container" class="alert alert-danger mt-4 d-none">
                <h5>❌ Error</h5>
                <p id="error-message"></p>
            </div>
        </div>

        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
        <script>
            let chart = null;
            const tableSchema = """ + json.dumps(TABLE_SCHEMA) + """;

            function updateColumns() {
                const table = document.getElementById('table-select').value;
                const columns = tableSchema[table] || [];

                const xAxisSelect = document.getElementById('x-axis');
                const yAxisSelect = document.getElementById('y-axis');
                const filterColumnSelect = document.getElementById('filter-column');

                xAxisSelect.innerHTML = '<option value="">Select column...</option>';
                yAxisSelect.innerHTML = '<option value="">Select column...</option>';
                filterColumnSelect.innerHTML = '<option value="">Column</option>';

                columns.forEach(col => {
                    xAxisSelect.innerHTML += `<option value="${col}">${col}</option>`;
                    yAxisSelect.innerHTML += `<option value="${col}">${col}</option>`;
                    filterColumnSelect.innerHTML += `<option value="${col}">${col}</option>`;
                });
            }

            async function generateVisualization() {
                const table = document.getElementById('table-select').value;
                const chartType = document.getElementById('chart-type').value;
                const xAxis = document.getElementById('x-axis').value;
                const yAxis = document.getElementById('y-axis').value;
                const aggregation = document.getElementById('aggregation').value;
                const filterColumn = document.getElementById('filter-column').value;
                const filterOperator = document.getElementById('filter-operator').value;
                const filterValue = document.getElementById('filter-value').value;
                const title = document.getElementById('chart-title').value;

                if (!table || !xAxis || !yAxis) {
                    showError('Please select table, X-axis, and Y-axis columns');
                    return;
                }

                document.getElementById('loading-spinner').classList.remove('d-none');
                document.getElementById('error-container').classList.add('d-none');

                try {
                    const params = new URLSearchParams({
                        table: table,
                        chart_type: chartType,
                        x_axis: xAxis,
                        y_axis: yAxis,
                        aggregation: aggregation,
                        title: title
                    });

                    if (filterColumn && filterValue) {
                        params.append('filter_column', filterColumn);
                        params.append('filter_operator', filterOperator);
                        params.append('filter_value', filterValue);
                    }

                    const res = await fetch(`/api/visualize?${params}`);

                    if (!res.ok) {
                        const errorText = await res.text();
                        throw new Error(`Server Error (${res.status}): ${errorText}`);
                    }

                    const data = await res.json();

                    updateChart(data.chart_data, data.chart_title);
                    updateStats(data.statistics);
                    updateTable(data.raw_data);

                } catch (error) {
                    console.error('Error:', error);
                    showError(error.message);
                } finally {
                    document.getElementById('loading-spinner').classList.add('d-none');
                }
            }

            function updateChart(chartData, title) {
                const ctx = document.getElementById('chartCanvas').getContext('2d');

                if (chart) {
                    chart.destroy();
                }

                chart = new Chart(ctx, {
                    type: chartData.type,
                    data: {
                        labels: chartData.labels,
                        datasets: [{
                            label: title,
                            data: chartData.values,
                            backgroundColor: 'rgba(102, 126, 234, 0.6)',
                            borderColor: 'rgba(102, 126, 234, 1)',
                            borderWidth: 2,
                            tension: 0.4
                        }]
                    },
                    options: {
                        responsive: true,
                        plugins: {
                            title: { display: true, text: title }
                        }
                    }
                });
            }

            function updateStats(stats) {
                let html = '<h5>📊 Statistics</h5><ul class="list-group">';
                for (const [key, value] of Object.entries(stats)) {
                    const label = key.replace(/_/g, ' ').toUpperCase();
                    const val = typeof value === 'number' ? value.toFixed(2) : value;
                    html += `<li class="list-group-item d-flex justify-content-between"><span>${label}</span><strong>${val}</strong></li>`;
                }
                html += '</ul>';
                document.getElementById('stats-container').innerHTML = html;
            }

            function updateTable(data) {
                if (!data || data.length === 0) {
                    document.getElementById('table-container').innerHTML = '<p class="text-muted">No data available</p>';
                    return;
                }

                const columns = Object.keys(data[0]);
                let html = '<h5 class="mt-4">📋 Raw Data</h5><div class="table-responsive"><table class="table table-striped table-sm">';
                html += '<thead class="table-dark"><tr>';
                columns.forEach(col => html += `<th>${col.toUpperCase()}</th>`);
                html += '</tr></thead><tbody>';

                data.slice(0, 10).forEach(row => {
                    html += '<tr>';
                    columns.forEach(col => {
                        const val = row[col];
                        html += `<td>${typeof val === 'number' ? val.toFixed(2) : val}</td>`;
                    });
                    html += '</tr>';
                });

                html += '</tbody></table>';
                if (data.length > 10) {
                    html += `<p class="text-muted mt-2">Showing first 10 rows of ${data.length} total rows</p>`;
                }
                html += '</div>';
                document.getElementById('table-container').innerHTML = html;
            }

            function showError(message) {
                document.getElementById('error-message').textContent = message;
                document.getElementById('error-container').classList.remove('d-none');
            }

            function clearVisualization() {
                if (chart) {
                    chart.destroy();
                    chart = null;
                }
                document.getElementById('stats-container').innerHTML = '';
                document.getElementById('table-container').innerHTML = '';
                document.getElementById('error-container').classList.add('d-none');
            }

            // Initialize
            updateColumns();
        </script>
    </body>
    </html>
    """
    return html

@app.get("/api/visualize")
def create_visualization(
    table: str,
    chart_type: str,
    x_axis: str,
    y_axis: str,
    aggregation: str = "COUNT",
    title: str = "Custom Visualization",
    filter_column: Optional[str] = None,
    filter_operator: Optional[str] = None,
    filter_value: Optional[str] = None
):
    """Create dynamic visualizations based on user specifications"""
    try:
        # Validate inputs
        if table not in TABLE_SCHEMA:
            raise HTTPException(status_code=400, detail=f"Table '{table}' not found")

        if x_axis not in TABLE_SCHEMA[table]:
            raise HTTPException(status_code=400, detail=f"Column '{x_axis}' not found in table '{table}'")

        if y_axis not in TABLE_SCHEMA[table]:
            raise HTTPException(status_code=400, detail=f"Column '{y_axis}' not found in table '{table}'")

        # Build SQL query
        query_parts = []

        # SELECT clause
        if aggregation in ["COUNT", "SUM", "AVG", "MIN", "MAX"]:
            if aggregation == "COUNT":
                select_clause = f"SELECT {x_axis}, COUNT(*) as value"
            else:
                select_clause = f"SELECT {x_axis}, {aggregation}(COALESCE({y_axis}, 0)) as value"
        else:
            raise HTTPException(status_code=400, detail=f"Invalid aggregation: {aggregation}")

        query_parts.append(select_clause)

        # FROM clause
        query_parts.append(f"FROM {table}")

        # WHERE clause (if filter provided)
        where_conditions = []
        if filter_column and filter_operator and filter_value:
            if filter_column not in TABLE_SCHEMA[table]:
                raise HTTPException(status_code=400, detail=f"Filter column '{filter_column}' not found in table '{table}'")

            if filter_operator == "LIKE":
                where_conditions.append(f"{filter_column} LIKE '%{filter_value}%'")
            else:
                where_conditions.append(f"{filter_column} {filter_operator} '{filter_value}'")

        if where_conditions:
            query_parts.append("WHERE " + " AND ".join(where_conditions))

        # GROUP BY clause
        query_parts.append(f"GROUP BY {x_axis}")

        # ORDER BY clause
        query_parts.append("ORDER BY value DESC")

        # Execute query
        full_query = " ".join(query_parts)
        with engine.connect() as conn:
            df = pd.read_sql(text(full_query), conn)

        if df.empty:
            return {
                "chart_data": {"type": chart_type, "labels": [], "values": []},
                "chart_title": title,
                "statistics": {"total_records": 0, "message": "No data found with current filters"},
                "raw_data": []
            }

        # Clean data
        df = clean_dataframe(df)

        # Prepare response
        labels = df[x_axis].astype(str).tolist()
        values = df['value'].fillna(0).tolist()

        # Calculate statistics
        statistics = {
            "total_records": len(df),
            "total_value": sum(values),
            "average_value": sum(values) / len(values) if values else 0,
            "max_value": max(values) if values else 0,
            "min_value": min(values) if values else 0
        }

        return {
            "chart_data": {
                "type": chart_type,
                "labels": labels,
                "values": values
            },
            "chart_title": title,
            "statistics": statistics,
            "raw_data": df.to_dict(orient="records")
        }

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))

@app.get("/api/tables")
def get_tables():
    """Get available tables and their columns"""
    return {
        "tables": list(TABLE_SCHEMA.keys()),
        "schema": TABLE_SCHEMA
    }

@app.get("/api/table/{table_name}")
def get_table_info(table_name: str):
    """Get information about a specific table"""
    if table_name not in TABLE_SCHEMA:
        raise HTTPException(status_code=404, detail=f"Table '{table_name}' not found")

    try:
        # Get sample data
        query = text(f"SELECT * FROM {table_name} LIMIT 5")
        with engine.connect() as conn:
            df = pd.read_sql(query, conn)

        return {
            "table_name": table_name,
            "columns": TABLE_SCHEMA[table_name],
            "sample_data": df.to_dict(orient="records"),
            "total_rows": len(df)  # This is just sample, not total
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))